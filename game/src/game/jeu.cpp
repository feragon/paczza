#include <config.h>
#include "jeu.h"
#include "dumbmonstermanager.h"

Jeu::Jeu() {
    int i = 13;
    int j = 8;

    Position positionJoueur(3,5);
    Position m1(6,4);
    Position m2(6,5);
    Position m3(7,4);
    Position m4(7,5);

    Liste<Position>* positionsReservees = nullptr;
    positionsReservees = new Liste<Position>(&m1, positionsReservees);
    positionsReservees = new Liste<Position>(&m2, positionsReservees);
    positionsReservees = new Liste<Position>(&m3, positionsReservees);
    positionsReservees = new Liste<Position>(&m4, positionsReservees);
    positionsReservees = new Liste<Position>(&positionJoueur, positionsReservees);

    _plateau = new Board(i, j, positionsReservees);

    _joueur = new Pacman(positionJoueur);

    _monsterManager = new DumbMonsterManager(_plateau);

    _monstres = nullptr;
    for(Liste<Position>* monstres = positionsReservees->next; monstres; monstres = monstres->next) {
        Monster* monster = new Monster(*(monstres->value));
        _monsterManager->addMonster(monster);
        _monstres = new Liste<Monster>(monster, _monstres);
    }

    Liste<Position>::efface1(positionsReservees);

    _timeSinceMove = 0;
}

Jeu::~Jeu() {
    delete _plateau;
    delete _joueur;
    delete _monsterManager;
    Liste<Monster>::efface2(_monstres);
}

void Jeu::updateGame(double timeElapsed) {
    _timeSinceMove += timeElapsed;

    if(_timeSinceMove > MOVEMENT_TIME) {
        _timeSinceMove = 0;

        _monsterManager->moveMonsters();

        for(Liste<Monster>* monsters = _monstres; monsters; monsters = monsters->next) {
            monsters->value->setPosition(_monsterManager->newPosition(monsters->value));
        }
    }
}
