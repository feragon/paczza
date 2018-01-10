#include "menu.h"
#include <config.h>
#include <math.h>
#include <ui/spriteloader.h>

Menu::Menu(sf::RenderWindow* window) :
        View(window) {

}

void Menu::renderBackground() {
    for(sf::Sprite sprite : _backgroundSprites) {
        _window->draw(sprite);
    }
}

void Menu::resize(const sf::Vector2f& size) {
    for(unsigned int i = 0; i <= ceil(size.x / SPRITE_SIZE); i++) {
        for(unsigned int j = 0; j <= ceil(size.y / SPRITE_SIZE); j++) {
            sf::Sprite sprite(SpriteLoader::getSprite(SpriteLoader::EMPTY_CELL));
            sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }
}
