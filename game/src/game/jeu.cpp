#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) {
    _graphe = new Graphe<Case, Chemin>(8,5);
    _joueur = new Joueur(Position(getGraphe()->columns()/2,getGraphe()->rows()/2));

    int i = _graphe->columns();
    int j = _graphe->rows();

    _aliments.push_back(std::make_pair(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::TOMATO));
    _aliments.push_back(std::make_pair(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::CHEESE));
    _aliments.push_back(std::make_pair(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::HAM));
    _aliments.push_back(std::make_pair(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::MUSHROOM));
}

Graphe<Case, Chemin> * Jeu::getGraphe() {
    return _graphe;
};

Joueur * Jeu::getJoueur() {
    return _joueur;
}