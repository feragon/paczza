#include "fenetrejeu.h"
#include <config.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <ui/resourceloader.h>
#include <ui/views/mainmenu.h>

FenetreJeu::FenetreJeu() :
    _fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), TITRE_FENETRE) {

    _fenetre.setVerticalSyncEnabled(true);

    sf::Image image;
    image.loadFromFile("res/icon.png");
    _fenetre.setIcon(45, 45, image.getPixelsPtr());

    _view = new MainMenu(&_fenetre, this);

    resizeView(_fenetre.getSize());
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

            if (event.type == sf::Event::Resized) {
                resizeView(_fenetre.getSize());
            }

            _view->onEvent(event);
        }

        _fenetre.clear(sf::Color(0, 0, 0, 255));

        _view->render();

        _fenetre.display();
    }
}

void FenetreJeu::fermer() {
    _fenetre.close();
}

void FenetreJeu::resizeView(const sf::Vector2u& size) {
    sf::Vector2f newSize(size.x, size.y);
    _fenetre.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0), newSize)));
    _view->resize(newSize);
}

void FenetreJeu::changerVue(View *v) {
    _view = v;
    _view->resize(_fenetre.getView().getSize());
}