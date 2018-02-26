#include "dumbmonstermanager.h"
#include <game/jeu.h>

DumbMonsterManager::DumbMonsterManager(Jeu* game) :
        MonsterManager(game) {
    srand(time(NULL));
}

void DumbMonsterManager::moveMonster(const Monster* monster, const Position<>& playerPosition) {
    monsters()[monster] = getNextPosition(game()->plateau(), game()->plateau()->sommet(monster->position()->contenu().position()));
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
