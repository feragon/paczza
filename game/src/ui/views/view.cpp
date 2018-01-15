#include "view.h"

View::View(sf::RenderWindow* window, FenetreJeu* f) {
    _window = window;
    _fenetreJeu = f;
}

FenetreJeu* View::getFenetreJeu() {
    return _fenetreJeu;
}