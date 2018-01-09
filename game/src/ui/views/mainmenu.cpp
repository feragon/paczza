#include "mainmenu.h"
#include <config.h>
#include <ui/spriteloader.h>

MainMenu::MainMenu(sf::RenderWindow* window) :
    View(window) {

    for(unsigned int i = 0; i < LARGEUR_FENETRE / SPRITE_SIZE; i++) {
        for(unsigned int j = 0; j < HAUTEUR_FENETRE / SPRITE_SIZE; j++) {
            sf::Sprite sprite(SpriteLoader::getSprite(SpriteLoader::EMPTY_CELL));
            sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }
}

void MainMenu::render() {
    for(sf::Sprite sprite : _backgroundSprites) {
        _window->draw(sprite);
    }
}
