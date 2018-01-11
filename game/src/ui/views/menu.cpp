#include "menu.h"
#include <config.h>
#include <math.h>
#include <ui/spriteloader.h>
#include <iostream>
#include <SFML/Window/Event.hpp>

Menu::Menu(sf::RenderWindow* window) :
        View(window),
        _selector(SpriteLoader::getSprite(SpriteLoader::RIGHT_PINEAPPLE)) {

    _selected = 0;

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

    _window->draw(_selector);
}

void Menu::addMenu(const std::wstring& title) {
    sf::Text* text = new sf::Text(sf::String(title), _font, 42);
    _texts.push_back(text);
}

void Menu::centerTexts() {
    float halfWidth = _window->getView().getSize().x / 2;
    float halfHeight = _window->getView().getSize().y / 2;
    unsigned int i = 0;

    for(sf::Text* text : _texts) {
        text->setPosition(halfWidth - (text->getGlobalBounds().width / 2), halfHeight + (i * 45));
        i++;
    }

    updateSelectorPosition();
}

void Menu::updateSelectorPosition() {
    if(_texts.size() == 0) {
        return;
    }

    if(_selected >= _texts.size()) {
        _selected = 0;
    }

    sf::Vector2f position = _texts[_selected]->getPosition();
    float top = position.y;
    float left = position.x - 64;
    _selector.setPosition(left, top);
}

void Menu::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Down:
                if(_selected < _texts.size() - 1) {
                    _selected++;
                }
                updateSelectorPosition();
                break;

            case sf::Keyboard::Key::Up:
                if(_selected > 0) {
                    _selected--;
                }
                updateSelectorPosition();
                break;
        }


    }
}
