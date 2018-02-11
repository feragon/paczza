#include <astar/astart.h>
#include "astarmonstermanager.h"
#include "astarfunctions.h"
#include "dumbmonstermanager.h"

AStarMonsterManager::AStarMonsterManager(Board* board) :
        MonsterManager(board) {

}

void AStarMonsterManager::moveMonsters(const Position<>& playerPosition) {
    AStarFunctions::destination = board()->sommet(playerPosition);
    monsters().clear();
    for(Liste<Monster>* monster = board()->monsters(); monster; monster = monster->next) {
        Sommet<Case>* position = board()->sommet(monster->value->position()->contenu().position());
        Sommet<Case>* destination = AStarT<Graphe<Chemin, Case>, Sommet<Case>>::aStar(*board(), position, &AStarFunctions::hh);

        if(destination != AStarFunctions::destination) {
            monsters()[monster->value] = DumbMonsterManager::getNextPosition(board(), position);
        }
        else {
            while(destination->contenu().parent != nullptr && destination->contenu().parent != monster->value->position()) {
                destination = destination->contenu().parent;
            }

            monsters()[monster->value] = destination->contenu().position();
        }
    }
}