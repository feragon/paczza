#include "fenetrejeu.h"
#include <config.h>
#include <SFML/Window/Event.hpp>

FenetreJeu::FenetreJeu() :
    _fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), TITRE_FENETRE) {

    _fenetre.setVerticalSyncEnabled(true);
}

void FenetreJeu::ouvrir() {
    while (_fenetre.isOpen()) {

        sf::Event event;
        while (_fenetre.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                fermer();
        }

        // Clear screen
        _fenetre.clear(sf::Color(0, 0, 0, 255));
        // Update the window
        _fenetre.display();
    }
}

void FenetreJeu::fermer() {
    _fenetre.close();
}
