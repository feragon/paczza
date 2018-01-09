#include "spriteloader.h"
#include <config.h>
#include <iostream>

SpriteLoader SpriteLoader::_instance;

SpriteLoader::SpriteLoader() {
    sf::Image sprites;
    sprites.loadFromFile("res/sprites.png");

    unsigned int columns = sprites.getSize().x / SPRITE_SIZE;
    unsigned int lines = sprites.getSize().y / SPRITE_SIZE;

    if(columns * lines < FIN) {
        throw std::runtime_error("Nombre de sprites incorrect");
    }

    for(int i = 0; i < FIN; i++) {
        unsigned int line = i / columns;
        unsigned int column = i % columns;
        sf::Texture sprite;

        sprite.loadFromImage(sprites, sf::IntRect(column * SPRITE_SIZE, line * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE));

        _sprites[static_cast<Sprite>(i)] = sprite;
    }
}

const sf::Texture& SpriteLoader::getSprite(SpriteLoader::Sprite s) {
    return _instance._sprites.at(s);
}
