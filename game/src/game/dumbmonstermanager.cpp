#include "dumbmonstermanager.h"
#include <game/jeu.h>
#include <time.h>

DumbMonsterManager::DumbMonsterManager(Jeu* game) :
        MonsterManager(game) {
    srand(time(NULL));
}

void DumbMonsterManager::moveMonster(const Monster* monster, const Position<>& playerPosition) {
    monsters()[monster] = getNextPosition(game()->plateau(), game()->plateau()->sommet(monster->position()->contenu().position()));
}

Position<> DumbMonsterManager::getNextPosition(const Board<Element>* board, Sommet<Case<Element>>* monsterVertice) {
    Liste<Sommet<Case<Element>>>* vertices = board->voisins(monsterVertice);
    Liste<Sommet<Case<Element>>>* currentVertice = vertices;

    int verticeId = rand() % Liste<Sommet<Case<Element>>>::taille(vertices);

    for(int i = 0; i < verticeId; i++) {
        currentVertice = currentVertice->next;
    }

    Position<> res = currentVertice->value->contenu().position();
    Liste<Sommet<Case<Element>>>::efface1(vertices);

    return res;
}
