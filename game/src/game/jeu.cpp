#include <config.h>
#include "jeu.h"
#include <cmath>
#include "dumbmonstermanager.h"
#include "sensemonstermanager.h"
#include "noremaininglife.h"

Jeu::Jeu() :
        _originalPlayerPosition(3,5) {
    int i = 13;
    int j = 8;


    Position<> m1(6,4);
    Position<> m2(6,5);
    Position<> m3(7,4);
    Position<> m4(7,5);

    _originalMonstersPositions.push_back(m1);
    _originalMonstersPositions.push_back(m2);
    _originalMonstersPositions.push_back(m3);
    _originalMonstersPositions.push_back(m4);

    Liste<Position<>>* positionsReservees = nullptr;
    positionsReservees = new Liste<Position<>>(&m1, positionsReservees);
    positionsReservees = new Liste<Position<>>(&m2, positionsReservees);
    positionsReservees = new Liste<Position<>>(&m3, positionsReservees);
    positionsReservees = new Liste<Position<>>(&m4, positionsReservees);
    positionsReservees = new Liste<Position<>>(&_originalPlayerPosition, positionsReservees);

    _plateau = new Board(i, j, positionsReservees);

    _joueur = new Pacman(_plateau->sommet(_originalPlayerPosition), UP, 3);

    _monsterManager = new SenseMonsterManager(_plateau);

    _monstres = nullptr;
    for(Liste<Position<>>* monstres = positionsReservees->next; monstres; monstres = monstres->next) {
        Monster* monster = new Monster(_plateau->sommet(*(monstres->value)), UP);
        _monsterManager->addMonster(monster);
        _monstres = new Liste<Monster>(monster, _monstres);
    }

    Liste<Position<>>::efface1(positionsReservees);

    _stopped = true;
    _onPlayerPositionChanged = nullptr;
}

Jeu::~Jeu() {
    delete _plateau;
    delete _joueur;
    delete _monsterManager;
    Liste<Monster>::efface2(_monstres);
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
        movement = 0;

        _joueur->setPosition(_newPlayerPosition);
        _joueur->setAvancement(0);

        for(Liste<Monster>* monsters = _monstres; monsters; monsters = monsters->next) {
            Sommet<Case>* newPosition = _plateau->sommet(_monsterManager->newPosition(monsters->value));
            monsters->value->setPosition(newPosition);
            monsters->value->setAvancement(0);

            _oldPositions[monsters->value] = newPosition;

            if(newPosition == _joueur->position()) {
                _stopped = true;
            }
        }
        _monsterManager->moveMonsters(_newPlayerPosition->contenu().position());

        Direction oldDirection = _joueur->direction();
        _joueur->setDirection(_newDirection);
        const Sommet<Case>* nextPlayerPosition = getNextPlayerPosition();

        if(nextPlayerPosition == _newPlayerPosition && oldDirection != _joueur->direction()) {
            _joueur->setDirection(oldDirection);
            _newDirection = oldDirection;
            nextPlayerPosition = getNextPlayerPosition();
        }

        if (_onPlayerPositionChanged) {
            _onPlayerPositionChanged->onPlayerPositionChanged(_oldPositions[_joueur]->contenu().position(), _newPlayerPosition->contenu().position());
        }

        _oldPositions[_joueur] = _newPlayerPosition;
        _newPlayerPosition = nextPlayerPosition;
    }
    else {
        for(Liste<Monster>* monsters = _monstres; monsters; monsters = monsters->next) {
            Position<double> vect = _monsterManager->newPosition(monsters->value) - _oldPositions[monsters->value]->contenu().position();

            if(vect.x < 0) {
                if(vect.y == 0) {
                    monsters->value->setDirection(LEFT);
                }
                else if(vect.y < 0) {
                    monsters->value->setDirection(LEFT_UP);
                }
                else {
                    monsters->value->setDirection(LEFT_DOWN);
                }
            }
            else if(vect.x == 0) {
                if(vect.y < 0) {
                    monsters->value->setDirection(UP);
                }
                else {
                    monsters->value->setDirection(DOWN);
                }
            }
            else {
                if(vect.y == 0) {
                    monsters->value->setDirection(RIGHT);
                }
                else if(vect.y < 0) {
                    monsters->value->setDirection(RIGHT_UP);
                }
                else {
                    monsters->value->setDirection(RIGHT_DOWN);
                }
            }

            if(_monsterManager->newPosition(monsters->value) != _oldPositions[monsters->value]->contenu().position()) {
                monsters->value->setAvancement(movement);
            }
        }

        if(_joueur->position()->contenu().position() != _newPlayerPosition->contenu().position()) {
            _joueur->setAvancement(movement);
        }
    }

    for(Liste<Monster>* monsters = _monstres; monsters; monsters = monsters->next) {
        if(_plateau->getAreteParSommets(_joueur->position(), monsters->value->position()) &&
           movement >= 0.5) {
            if(abs(_joueur->direction() - monsters->value->direction()) == NB_DIRECTIONS/2 ||
                   _joueur->position() == _newPlayerPosition ||
                   monsters->value->position()->contenu().position() == _monsterManager->newPosition(monsters->value)) {
                _stopped = true;
            }
        }
    }
}

const Sommet<Case>* Jeu::getNextPlayerPosition() {
    const Sommet<Case>* actuelle = _joueur->position();

    Position<> moveVect;
    switch (_joueur->direction()) {
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
            if(sommet->value->first->contenu().position() == next
               && sommet->value->second->contenu().estAccessible()) {

                Arete<Chemin, Case>* arete = sommet->value->second;
                arete->contenu().setChaleur(UINT8_MAX);

                sommet->value->first->contenu().heberge(*(_joueur));

                const Sommet<Case>* nextVertice = sommet->value->first;
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

        _oldPositions[_joueur] = _plateau->sommet(_originalPlayerPosition);
        _joueur->setDirection(UP);
        _newDirection = UP;
        joueur()->setPosition(_plateau->sommet(_originalPlayerPosition));
        _newPlayerPosition = getNextPlayerPosition();

        int i = 0;
        for(Liste<Monster>* monsters = monstres(); monsters; monsters = monsters->next) {
            monsters->value->setPosition(_plateau->sommet(_originalMonstersPositions[i]));
            _oldPositions[monsters->value] = _plateau->sommet(_originalMonstersPositions[i]);
            i++;
        }

        _monsterManager->reset();

        for(Liste<Arete<Chemin, Case>>* aretes = _plateau->aretes(); aretes; aretes = aretes->next) {
            aretes->value->contenu().setChaleur(0);
        }

        _stopped = false;
    }
    catch(NoRemainingLife e) {

    }
}
