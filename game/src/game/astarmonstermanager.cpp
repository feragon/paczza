#include <astar/astart.h>
#include "astarmonstermanager.h"
#include "astarfunctions.h"
#include "dumbmonstermanager.h"
#include <game/jeu.h>

AStarMonsterManager::AStarMonsterManager(Jeu* game) :
        MonsterManager(game) {

}

void AStarMonsterManager::moveMonsters(const Position<>& playerPosition) {
    AStarFunctions::destination = game()->plateau()->sommet(playerPosition);
    monsters().clear();
    for(Liste<Monster>* monster = game()->monsters(); monster; monster = monster->next) {
        Sommet<Case>* position = game()->plateau()->sommet(monster->value->position()->contenu().position());
        Sommet<Case>* destination = AStarT<Graphe<Chemin, Case>, Sommet<Case>>::aStar(*(game()->plateau()), position, &AStarFunctions::hh);

        if(destination != AStarFunctions::destination) {
            monsters()[monster->value] = DumbMonsterManager::getNextPosition(game()->plateau(), position);
        }
        else {
            while(destination->contenu().parent != nullptr && destination->contenu().parent != monster->value->position()) {
                destination = destination->contenu().parent;
            }

            monsters()[monster->value] = destination->contenu().position();
        }
    }
}