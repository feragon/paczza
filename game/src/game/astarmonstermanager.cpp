#include <astar/astart.h>
#include "astarmonstermanager.h"
#include "astarfunctions.h"
#include "dumbmonstermanager.h"

AStarMonsterManager::AStarMonsterManager(Board* board) :
        MonsterManager(board) {

}

void AStarMonsterManager::moveMonsters(const Position<>& playerPosition) {
    AStarFunctions::destination = board()->sommet(playerPosition);
    for(std::pair<const Monster*, Position<>> pair : monsters()) {
        Sommet<Case>* position = board()->sommet(pair.first->position()->contenu().position());
        Sommet<Case>* destination = AStarT<Graphe<Chemin, Case>, Sommet<Case>>::aStar(*board(), position, &AStarFunctions::hh);

        if(destination != AStarFunctions::destination) {
            monsters()[pair.first] = DumbMonsterManager::getNextPosition(board(), position);
        }
        else {
            while(destination->contenu().parent != nullptr && destination->contenu().parent != pair.first->position()) {
                destination = destination->contenu().parent;
            }

            monsters()[pair.first] = destination->contenu().position();
        }
    }
}