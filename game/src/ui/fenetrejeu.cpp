#include "fenetrejeu.h"
#include <config.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <ui/spriteloader.h>
#include <ui/views/mainmenu.h>

FenetreJeu::FenetreJeu() :
    _fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), TITRE_FENETRE) {

    _fenetre.setVerticalSyncEnabled(true);

    sf::Image image;
    image.loadFromFile("res/icon.png");
    _fenetre.setIcon(45, 45, image.getPixelsPtr());

    _view = new MainMenu(&_fenetre);
}

FenetreJeu::~FenetreJeu() {
    delete _view;
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

        _view->render();

        // Update the window
        _fenetre.display();
    }
}

void FenetreJeu::fermer() {
    _fenetre.close();
}
