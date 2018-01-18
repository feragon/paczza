#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) {
    _plateau = new Board(13,8);

    int i = _plateau->width();
    int j = _plateau->height();

    _joueur = new Joueur(Position(i / 2, j / 2));

    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::TOMATO, 50));
    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::CHEESE, 50));
    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::HAM, 50));
    _aliments.push_back(new ElementGraphique(Position((rand() % i) + 1, (rand() % j) + 1), Sprite::MUSHROOM, 50));
}

Jeu::~Jeu() {
    delete _plateau;
    delete _joueur;
}

Board* Jeu::plateau() {
    return _plateau;
};

Joueur * Jeu::joueur() {
    return _joueur;
}

std::vector<ElementGraphique*>& Jeu::aliments() {
    return _aliments;
}
