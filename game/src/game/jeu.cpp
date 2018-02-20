#include <config.h>
#include "jeu.h"
#include <cmath>
#include <board/point.h>
#include "noremaininglife.h"
#include "astarmonstermanager.h"
#include "util.h"

Jeu::Jeu() {
    _monsterManager = nullptr;
    _plateau = new Board();

    updateOldPositions();

    _stopped = true;

    updatePoints();
}

Jeu::~Jeu() {
    delete _plateau;
    //delete _monsterManager; TODO
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

    if(_timeSinceMove >= MOVEMENT_TIME) {
        _timeSinceMove = 0;

        Arete<Chemin, Case>* arete = _plateau->getAreteParSommets(joueur()->position(), _newPlayerPosition);
        if(arete && arete->contenu().estAccessible()) {
            arete->contenu().setChaleur(UINT8_MAX);
            Listened<BoardListener>::callListeners(&BoardListener::updateEdge, arete);
        }

        Element* e = _newPlayerPosition->contenu().element();
        if(e) {
            _remainingPoints -= (bool) dynamic_cast<Point*>(e);
            if(_remainingPoints == 0) {
                _stopped = true;
            }
        }

        joueur()->setPosition(_newPlayerPosition);
        _newPlayerPosition->contenu().heberge(*joueur());
        Listened<BoardListener>::callListeners(&BoardListener::updateVertice, _newPlayerPosition);

        joueur()->setAvancement(0);

        if(_monsterManager) {
            for (Liste<Monster>* monsters = monstres(); monsters; monsters = monsters->next) {
                try {
                    Sommet<Case>* newPosition = _plateau->sommet(_monsterManager->newPosition(monsters->value));
                    monsters->value->setPosition(newPosition);
                    monsters->value->setAvancement(0);

                    _oldPositions[monsters->value] = newPosition;

                    if (newPosition == joueur()->position()) {
                        _stopped = true;
                    }
                }
                catch (std::out_of_range& e) {

                }
            }
            _monsterManager->moveMonsters(_newPlayerPosition->contenu().position());
        }

        Direction oldDirection = joueur()->direction();
        joueur()->setDirection(_newDirection);
        Sommet<Case>* nextPlayerPosition = getNextPlayerPosition();

        if(nextPlayerPosition == _newPlayerPosition && oldDirection != joueur()->direction()) {
            joueur()->setDirection(oldDirection);
            _newDirection = oldDirection;
            nextPlayerPosition = getNextPlayerPosition();
        }

        _oldPositions[joueur()] = joueur()->position();
        _newPlayerPosition = nextPlayerPosition;

        if(joueur()->position() != _newPlayerPosition) {
            Listened<BoardListener>::callListeners(&BoardListener::playerMovementBegin, joueur());
        }

        Listened<BoardListener>::callListeners(&BoardListener::onNewTurn);
    }
    else {
        if (_monsterManager) {
            for (Liste<Monster>* monsters = monstres(); monsters; monsters = monsters->next) {
                try {
                    Position<double> vect = _monsterManager->newPosition(monsters->value) -
                                            _oldPositions[monsters->value]->contenu().position();

                    if (vect.x < 0) {
                        if (vect.y == 0) {
                            monsters->value->setDirection(LEFT);
                        } else if (vect.y < 0) {
                            monsters->value->setDirection(LEFT_UP);
                        } else {
                            monsters->value->setDirection(LEFT_DOWN);
                        }
                    } else if (vect.x == 0) {
                        if (vect.y < 0) {
                            monsters->value->setDirection(UP);
                        } else {
                            monsters->value->setDirection(DOWN);
                        }
                    } else {
                        if (vect.y == 0) {
                            monsters->value->setDirection(RIGHT);
                        } else if (vect.y < 0) {
                            monsters->value->setDirection(RIGHT_UP);
                        } else {
                            monsters->value->setDirection(RIGHT_DOWN);
                        }
                    }

                    if (_monsterManager->newPosition(monsters->value) !=
                        _oldPositions[monsters->value]->contenu().position()) {
                        monsters->value->setAvancement(movement);
                    }
                }
                catch (std::out_of_range& e) {

                }
            }
        }

        if (joueur()->position()->contenu().position() != _newPlayerPosition->contenu().position()) {
            joueur()->setAvancement(movement);
        }

        if(_monsterManager && movement >= 0.5) {
            for (Liste<Monster>* monsters = monstres(); monsters; monsters = monsters->next) {
                Arete<Chemin, Case>* arete = _plateau->getAreteParSommets(joueur()->position(), monsters->value->position());
                if(!arete) {
                    continue;
                }

                if(getDirection(monsters->value->position()->contenu().position(), joueur()->position()->contenu().position()) != monsters->value->direction()) {
                    return;
                }

                if (abs(joueur()->direction() - monsters->value->direction()) == NB_DIRECTIONS / 2 ||
                    joueur()->position() == _newPlayerPosition) {
                    _stopped = true;
                }
            }
        }
    }
}

Sommet<Case>* Jeu::getNextPlayerPosition() {
    Sommet<Case>* actuelle = _plateau->sommet(joueur()->position()->contenu().position());

    Position<> moveVect;
    switch (joueur()->direction()) {
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

    Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>* voisins = _plateau->adjacences(actuelle);

    for(Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>* sommet = voisins; sommet; sommet = sommet->next) {
        try {
            if(sommet->value->first->contenu().position() == next && sommet->value->second->contenu().estAccessible()) {

                Sommet<Case>* nextVertice = sommet->value->first;
                Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>::efface2(voisins);
                return nextVertice;
            }
        }
        catch(std::exception e) {}
    }

    Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>::efface2(voisins);
    return actuelle;
}

void Jeu::start() {
    if(!_stopped) {
        return;
    }

    try {
        joueur()->takeLife();

        _timeSinceMove = 0;

        _plateau->placePlayers();
        updateOldPositions();
        _newDirection = UP;
        _newPlayerPosition = getNextPlayerPosition();

        _monsterManager->moveMonsters(joueur()->position()->contenu().position());

        for(Liste<Arete<Chemin, Case>>* aretes = _plateau->aretes(); aretes; aretes = aretes->next) {
            if(aretes->value->contenu().estAccessible())
                aretes->value->contenu().setChaleur(0);
        }

        Listened<BoardListener>::callListeners(&BoardListener::onNewTurn);
        _stopped = false;
    }
    catch(NoRemainingLife& e) {

    }
}

void Jeu::setMonsterManager(MonsterManager* monsterManager) {
    _monsterManager = monsterManager;
}

void Jeu::updateOldPositions() {
    _oldPositions[joueur()] = joueur()->position();
    for(Liste<Monster>* monsters = monstres(); monsters; monsters = monsters->next) {
        _oldPositions[monsters->value] = monsters->value->position();
    }
}

void Jeu::updatePoints() {
    _remainingPoints = 0;
    for(Liste<Sommet<Case>>* sommets = _plateau->sommets(); sommets; sommets = sommets->next) {
        Element* e = sommets->value->contenu().element();
        if(e) {
            _remainingPoints += (bool) dynamic_cast<Point*>(e);
        }
    }
}
