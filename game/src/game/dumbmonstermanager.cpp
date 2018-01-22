#include "dumbmonstermanager.h"

DumbMonsterManager::DumbMonsterManager(const Board* board) :
        MonsterManager(board) {
}

void DumbMonsterManager::moveMonsters() {
    for(std::pair<const Monster* const, Position<double>> pair : monsters()) {
        Liste<Sommet<Case>>* vertices = board()->voisins(board()->sommet(pair.first->position()));
        Liste<Sommet<Case>>* currentVertice = vertices;
        int verticeId = rand() % Liste<Sommet<Case>>::taille(vertices);

        for(int i = 0; i < verticeId; i++) {
            currentVertice = currentVertice->next;
        }

        monsters()[pair.first] = currentVertice->value->contenu().position();

        Liste<Sommet<Case>>::efface1(vertices);
    }
}
