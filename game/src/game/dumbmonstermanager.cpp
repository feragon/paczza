#include "dumbmonstermanager.h"

DumbMonsterManager::DumbMonsterManager(Board* board) :
        MonsterManager(board) {
    srand(time(NULL));
}

void DumbMonsterManager::moveMonsters(const Position<>& playerPosition) {
    for(std::pair<const Monster* const, Position<double>> pair : monsters()) {
        monsters()[pair.first] = getNextPosition(board(), board()->sommet(pair.first->position()->contenu().position()));
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
