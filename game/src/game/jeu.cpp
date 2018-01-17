#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) {
    _graphe = new Graphe<Case, Chemin>(12,8);
    _joueur = new Joueur(Position(getGraphe()->columns()/2,getGraphe()->rows()/2));

    int i = _graphe->columns();
    int j = _graphe->rows();

    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::TOMATO, 200));
    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::CHEESE, 200));
    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::HAM, 200));
    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::MUSHROOM, 200));
}

Graphe<Case, Chemin> * Jeu::getGraphe() {
    return _graphe;
};

Joueur * Jeu::getJoueur() {
    return _joueur;
}