#include "fenetrejeu.h"
#include <config.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <ui/spriteloader.h>

FenetreJeu::FenetreJeu() :
    _fenetre(sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE), TITRE_FENETRE) {

    _fenetre.setVerticalSyncEnabled(true);
}

void FenetreJeu::ouvrir() {
    //TODO: utilisé pour les tests, à enlever
    std::vector<sf::Sprite> sprites;
    for(unsigned int i = 0; i < LARGEUR_FENETRE / SPRITE_SIZE; i++) {
        for(unsigned int j = 0; j < HAUTEUR_FENETRE / SPRITE_SIZE; j++) {
            sf::Sprite sprite(SpriteLoader::getSprite(SpriteLoader::EMPTY_CELL));
            sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
            sprites.push_back(sprite);
        }
    }

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

        for(sf::Sprite sprite : sprites) {
            _fenetre.draw(sprite);
        }

        // Update the window
        _fenetre.display();
    }
}

void FenetreJeu::fermer() {
    _fenetre.close();
}
