#include <config.h>
#include "jeu.h"
#include <cmath>
#include <game/point.h>
#include <game/superpoint.h>
#include "util.h"
#include "pacmandied.h"
#include "teleporter.h"

Jeu::Jeu(SharedPtr<Board<Element>> board, GameData* gameData) :
    _monsterManager(nullptr),
    _player(nullptr, UP, 3),
    _monsters(nullptr) {

    _board = board;
    _gameData = gameData->clone();
    _gameData->placeElements(this);
    _gameData->placePlayers(this);

    updateOldPositions();

    _stopped = true;

    updatePoints();
}

Jeu::~Jeu() {
    Liste<Monster>::efface2(_monsters);
    delete _gameData;
}

void Jeu::updateGame(double timeElapsed) {
    updatePlayers(timeElapsed);
}

void Jeu::updatePlayers(double timeElapsed) {
    if(_stopped) {
        return;
    }

    _timeSinceMove += timeElapsed;
    double movement = _timeSinceMove / MOVEMENT_TIME;

    for (Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
        monsters->value->update(timeElapsed);
    }

    try {
        if (_timeSinceMove >= MOVEMENT_TIME) {
            _timeSinceMove = 0;

            Arete<Chemin, Case<Element>>* arete = _board->getAreteParSommets(_player.position(), _newPlayerPosition);
            if (arete && arete->contenu().estAccessible()) {
                arete->contenu().setChaleur(UINT8_MAX);
                Listened<GameListener>::callListeners(&GameListener::updateEdge, arete);
            }

            Element* e = _newPlayerPosition->contenu().element();
            if (e) {
                _remainingPoints -= (bool) dynamic_cast<Point*>(e);
                if (_remainingPoints == 0) {
                    _stopped = true;
                }
            }

            _player.setPosition(_newPlayerPosition);
            Element* element = _newPlayerPosition->contenu().element();
            if(element) {
                if(!element->traversePar(_player)) {
                    _newPlayerPosition->contenu().setElement(nullptr);
                };
            }

            _player.setAvancement(0);

            if (_monsterManager) {
                for (Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
                    try {
                        Sommet<Case<Element>>* newPosition = _board->sommet(_monsterManager->newPosition(monsters->value));
                        monsters->value->setPosition(newPosition);
                        monsters->value->setAvancement(0);

                        _oldPositions[monsters->value] = newPosition;

                        if (newPosition == _player.position()) {
                            monsters->value->collision(_player);
                            Listened<GameListener>::callListeners(&GameListener::onMonsterWeaknessUpdate, monsters->value);
                        }
                    }
                    catch (std::out_of_range& e) {

                    }
                }
                _monsterManager->moveMonsters(_newPlayerPosition->contenu().position());

                for (Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
                    try {
                        monsters->value->setDirection(getDirection(_oldPositions[monsters->value]->contenu().position(),
                                                                   _monsterManager->newPosition(monsters->value)));
                    }
                    catch (std::out_of_range& e) {

                    }
                }
            }

            Direction oldDirection = _player.direction();
            _player.setDirection(_newDirection);
            Sommet<Case<Element>>* nextPlayerPosition = getNextPlayerPosition();

            if (nextPlayerPosition == _newPlayerPosition && oldDirection != _player.direction()) {
                _player.setDirection(oldDirection);
                _newDirection = oldDirection;
                nextPlayerPosition = getNextPlayerPosition();
            }

            Listened<GameListener>::callListeners(&GameListener::onNewTurn);
            Listened<GameListener>::callListeners(&GameListener::updateVertice, _newPlayerPosition);

            _oldPositions[&_player] = _player.position();
            _newPlayerPosition = nextPlayerPosition;

            if (_player.position() != _newPlayerPosition) {
                Listened<GameListener>::callListeners(&GameListener::playerMovementBegin, &_player);
            }
        }
        else {
            if (_monsterManager) {
                for (Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
                    try {
                        if (_monsterManager->newPosition(monsters->value) !=
                            _oldPositions[monsters->value]->contenu().position()) {
                            monsters->value->setAvancement(movement);
                        }
                    }
                    catch (std::out_of_range& e) {

                    }
                }
            }

            if (_player.position()->contenu().position() != _newPlayerPosition->contenu().position()) {
                _player.setAvancement(movement);
            }

            if (_monsterManager && movement >= 0.5) {
                for (Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
                    Arete<Chemin, Case<Element>>* arete = _board->getAreteParSommets(_player.position(),
                                                                              monsters->value->position());
                    if (!arete) {
                        continue;
                    }

                    if (getDirection(monsters->value->position()->contenu().position(),
                                     _player.position()->contenu().position()) != monsters->value->direction()) {
                        continue;
                    }

                    if (abs(_player.direction() - monsters->value->direction()) == NB_DIRECTIONS / 2 ||
                        _player.position() == _newPlayerPosition) {
                        monsters->value->collision(_player);
                        Listened<GameListener>::callListeners(&GameListener::onMonsterWeaknessUpdate, monsters->value);
                    }
                }
            }
        }
    }
    catch (PacmanDied& e) {
        _stopped = true;
    }
}

Sommet<Case<Element>>* Jeu::getNextPlayerPosition() {
    Sommet<Case<Element>>* actuelle = _board->sommet(_player.position()->contenu().position());

    Position<> moveVect;
    switch (_player.direction()) {
        case LEFT:
            moveVect = Position<>(-1, 0);
            break;

        case RIGHT:
            moveVect = Position<>(1, 0);
            break;

        case UP:
            moveVect = Position<>(0, -1);
            break;

        case DOWN:
            moveVect = Position<>(0, 1);
            break;

        case LEFT_UP:
            moveVect = Position<>(-1, -1);
            break;

        case LEFT_DOWN:
            moveVect = Position<>(-1, 1);
            break;

        case RIGHT_UP:
            moveVect = Position<>(1, -1);
            break;

        case RIGHT_DOWN:
            moveVect = Position<>(1, 1);
            break;
    }

    Position<> next = actuelle->contenu().position() + moveVect;

    Liste<std::pair<Sommet<Case<Element>>*, Arete<Chemin, Case<Element>>*>>* voisins = _board->adjacences(actuelle);

    for(Liste<std::pair<Sommet<Case<Element>>*, Arete<Chemin, Case<Element>>*>>* sommet = voisins; sommet; sommet = sommet->next) {
        try {
            if(sommet->value->first->contenu().position() == next && sommet->value->second->contenu().estAccessible()) {

                Sommet<Case<Element>>* nextVertice = sommet->value->first;
                Liste<std::pair<Sommet<Case<Element>>*, Arete<Chemin, Case<Element>>*>>::efface2(voisins);
                return nextVertice;
            }
        }
        catch(std::exception& e) {

        }
    }

    Liste<std::pair<Sommet<Case<Element>>*, Arete<Chemin, Case<Element>>*>>::efface2(voisins);
    return actuelle;
}

void Jeu::start() {
    if(!_stopped) {
        return;
    }

    _player.takeLife();

    _timeSinceMove = 0;

    Liste<Monster>::efface2(_monsters);
    _gameData->placePlayers(this);

    updateOldPositions();
    _newDirection = UP;
    _newPlayerPosition = getNextPlayerPosition();

    for(Liste<Arete<Chemin, Case<Element>>>* aretes = _board->aretes(); aretes; aretes = aretes->next) {
        if(aretes->value->contenu().estAccessible()) {
            aretes->value->contenu().setChaleur(0);
        }
    }

    _monsterManager->moveMonsters(_player.position()->contenu().position());

    for (Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
        try {
            monsters->value->setDirection(getDirection(_oldPositions[monsters->value]->contenu().position(),
                                                       _monsterManager->newPosition(monsters->value)));
        }
        catch (std::out_of_range& e) {

        }
    }

    Listened<GameListener>::callListeners(&GameListener::onNewTurn);
    _stopped = false;
}

void Jeu::updateOldPositions() {
    _oldPositions[&_player] = _player.position();
    for(Liste<Monster>* monsters = _monsters; monsters; monsters = monsters->next) {
        _oldPositions[monsters->value] = monsters->value->position();
    }
}

void Jeu::updatePoints() {
    _remainingPoints = 0;
    for(Liste<Sommet<Case<Element>>>* sommets = _board->sommets(); sommets; sommets = sommets->next) {
        Element* e = sommets->value->contenu().element();
        if(e) {
            _remainingPoints += (bool) dynamic_cast<Point*>(e);
        }
    }
}

void Jeu::setMonstersWeak() {
    for(Liste<Monster>* monster = _monsters; monster; monster = monster->next) {
        monster->value->setWeak(true);
        Listened<GameListener>::callListeners(&GameListener::onMonsterWeaknessUpdate, monster->value);
    }
}

void Jeu::addMonster(Sommet<Case<Element>>* position) {
    position->contenu().setElement(nullptr);
    _monsters = new Liste<Monster>(new Monster(position, UP, position), _monsters);
}