#include "menu.h"
#include <config.h>
#include <math.h>
#include <ui/spriteloader.h>
#include <iostream>

Menu::Menu(sf::RenderWindow* window) :
        View(window) {

    if (!_font.loadFromFile("res/fonts/Pixellari.ttf")) {
        throw std::runtime_error("Impossible de lire la police de caractères.");
    }
}

Menu::~Menu() {
    for(sf::Text* text : _texts) {
        delete text;
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

    centerTexts();
}

void Menu::render() {
    for(sf::Sprite sprite : _backgroundSprites) {
        _window->draw(sprite);
    }

    for(sf::Text* text : _texts) {
        _window->draw(*text);
    }
}

void Menu::addMenu(const std::wstring& title) {
    sf::Text* text = new sf::Text(sf::String(title), _font, 18);
    _texts.push_back(text);
}

void Menu::centerTexts() {
    float halfWidth = _window->getView().getSize().x / 2;
    float halfHeight = _window->getView().getSize().y / 2;
    unsigned int i = 0;

    for(sf::Text* text : _texts) {
        text->setPosition(halfWidth - (text->getGlobalBounds().width / 2), halfHeight + (i * 20));
        i++;
    }
}
