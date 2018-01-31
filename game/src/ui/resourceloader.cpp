#include "resourceloader.h"
#include <config.h>
#include <iostream>

ResourceLoader ResourceLoader::_instance;

ResourceLoader::ResourceLoader() {
    loadSprites();
    loadFonts();
    loadSounds();
}

void ResourceLoader::loadSprites() {
    sf::Image sprites;

    if(!sprites.loadFromFile("res/sprites.png")) {
        throw std::runtime_error("Impossible de lire les sprites");
    }

    unsigned int columns = sprites.getSize().x / SPRITE_SIZE;
    unsigned int lines = sprites.getSize().y / SPRITE_SIZE;

    if(columns * lines < SPRITE_FIN) {
        throw std::runtime_error("Nombre de sprites incorrect");
    }

    for(int i = 0; i < SPRITE_FIN; i++) {
        unsigned int line = i / columns;
        unsigned int column = i % columns;
        sf::Texture sprite;

        sprite.loadFromImage(sprites, sf::IntRect(column * SPRITE_SIZE, line * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE));

        _sprites[static_cast<Sprite>(i)] = sprite;
    }
}

void ResourceLoader::loadFonts() {
    if(fontPath.size() != FONT_FIN) {
        throw std::runtime_error("Nombre de chemins de polices de caractère incorrect.");
    }

    for(int i = 0; i < FONT_FIN; i++) {
        Font font = static_cast<Font>(i);
        sf::Font sfFont;

        sfFont.loadFromFile(std::string("res/fonts/") + fontPath.at(font)); //TODO: get path

        _fonts[font] = sfFont;
    }
}

void ResourceLoader::loadSounds() {
    if(soundPath.size() != SOUND_FIN) {
        throw std::runtime_error("Nombre de chemins de sons incorrect.");
    }

    for(int i = 0; i < SOUND_FIN; i++) {
        Sound sound = static_cast<Sound>(i);
        sf::SoundBuffer sfSoundB;

        sfSoundB.loadFromFile(std::string("res/sounds/") + soundPath.at(sound)); //TODO: get path

        _sounds[sound] = sfSoundB;
    }
}

const sf::Texture& ResourceLoader::getSprite(Sprite s) {
    return _instance._sprites.at(s);
}

const sf::Font& ResourceLoader::getFont(Font f) {
    return _instance._fonts.at(f);
}

const sf::SoundBuffer& ResourceLoader::getSound(Sound s) {
    return _instance._sounds.at(s);
}