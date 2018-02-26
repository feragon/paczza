#include <astar/astart.h>
#include "astarmonstermanager.h"
#include "astarfunctions.h"
#include "dumbmonstermanager.h"
#include <game/jeu.h>

AStarMonsterManager::AStarMonsterManager(Jeu* game) :
        MonsterManager(game) {

}

void AStarMonsterManager::moveMonster(const Monster* monster, const Position<>& playerPosition) {
    AStarFunctions::destination = game()->plateau()->sommet(playerPosition);

    Sommet<Case>* position = game()->plateau()->sommet(monster->position()->contenu().position());
    Sommet<Case>* destination = AStarT<Graphe<Chemin, Case>, Sommet<Case>>::aStar(*(game()->plateau()), position, &AStarFunctions::hh);

    if(destination != AStarFunctions::destination) {
        monsters()[monster] = DumbMonsterManager::getNextPosition(game()->plateau(), position);
    }
    else {
        while(destination->contenu().parent != nullptr && destination->contenu().parent != monster->position()) {
            destination = destination->contenu().parent;
        }

        monsters()[monster] = destination->contenu().position();
    }
}