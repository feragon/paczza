#include "dumbmonstermanager.h"
#include <game/jeu.h>

DumbMonsterManager::DumbMonsterManager(Jeu* game) :
        MonsterManager(game) {
    srand(time(NULL));
}

void DumbMonsterManager::moveMonsters(const Position<>& playerPosition) {
    monsters().clear();
    for(Liste<Monster>* monster = game()->monsters(); monster; monster = monster->next) {
        monsters()[monster->value] = getNextPosition(game()->plateau(), game()->plateau()->sommet(monster->value->position()->contenu().position()));
    }
}

Position<> DumbMonsterManager::getNextPosition(const Board* board, Sommet<Case>* monsterVertice) {
    Liste<Sommet<Case>>* vertices = board->voisins(monsterVertice);
    Liste<Sommet<Case>>* currentVertice = vertices;

    int verticeId = rand() % Liste<Sommet<Case>>::taille(vertices);

    for(int i = 0; i < verticeId; i++) {
        currentVertice = currentVertice->next;
    }

    Position<> res = currentVertice->value->contenu().position();
    Liste<Sommet<Case>>::efface1(vertices);

    return res;
}
