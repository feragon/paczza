#include <astar/astart.h>
#include "monstermanager.h"
#include "jeu.h"
#include "astarfunctions.h"

MonsterManager::MonsterManager(Jeu* game) {
    _game = game;
}

Position<double> MonsterManager::newPosition(const Monster* monster) const {
    return _newPositions.at(monster);
}

void MonsterManager::moveMonsters(const Position<>& playerPosition) {
    monsters().clear();

    for(Liste<Monster>* monster = game()->monsters(); monster; monster = monster->next) {
        if(monster->value->returnHome()) {
            sendHome(monster->value);
        }
        else {
            moveMonster(monster->value, playerPosition);
        }
    }
}

void MonsterManager::sendHome(const Monster* monster) {
    if(monster->position() == monster->home()) {
        return;
    }
    AStarFunctions::destination = monster->home();

    Sommet<Case<Element>>* position = game()->plateau()->sommet(monster->position()->contenu().position());
    Sommet<Case<Element>>* destination = AStarT<Graphe<Chemin, Case<Element>>, Sommet<Case<Element>>>::aStar(*(game()->plateau()), position, &AStarFunctions::hh);

    if(destination != AStarFunctions::destination) {
        std::cerr << "Impossible de trouver un chemin jusqu'à la case d'origine" << std::endl;
    }
    else {
        while(destination->contenu().parent != nullptr && destination->contenu().parent != monster->position()) {
            destination = destination->contenu().parent;
        }

        _newPositions.insert(std::pair<const Monster*, Position<double>>(monster, destination->contenu().position()));
    }
}
