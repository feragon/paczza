#include "menu.h"
#include "ui/views/boardview.h"
#include <config.h>
#include <math.h>
#include <ui/resourceloader.h>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <game/jeu.h>

Menu::Menu(sf::RenderWindow* window) :
        View(window),
        _selector(ResourceLoader::getSprite(Sprite::RIGHT_PINEAPPLE)) {

    _selected = 0;
}

Menu::~Menu() {
    for(MenuItem* item : _items) {
        delete item;
    }
}

void Menu::resize(const sf::Vector2f& size) {
    for(unsigned int i = 0; i <= ceil(size.x / SPRITE_SIZE); i++) {
        for(unsigned int j = 0; j <= ceil(size.y / SPRITE_SIZE); j++) {
            sf::Sprite sprite(ResourceLoader::getSprite(Sprite::EMPTY_CELL));
            sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }

    centerTexts();
}

void Menu::addItem(MenuItem* item) {
    _items.push_back(item);
}

void Menu::render() {
    for(sf::Sprite sprite : _backgroundSprites) {
        _window->draw(sprite);
    }

    for(MenuItem* item : _items) {
        _window->draw(*item);
    }

    _window->draw(_selector);
}

void Menu::centerTexts() {
    float halfWidth = _window->getView().getSize().x / 2;
    float halfHeight = _window->getView().getSize().y / 2;
    unsigned int i = 0;

    for(MenuItem* item : _items) {
        item->setPosition(sf::Vector2f(halfWidth - (item->bounds().width / 2), halfHeight + (i * 45)));
        i++;
    }

    updateSelectorPosition();
}

void Menu::updateSelectorPosition() {
    if(_items.size() == 0) {
        return;
    }

    if(_selected >= _items.size()) {
        _selected = 0;
    }

    sf::Vector2f position = _items[_selected]->position();

    float top = position.y + (_items[_selected]->bounds().height - _selector.getLocalBounds().height) / 2;
    float left = position.x - _selector.getLocalBounds().width;
    _selector.setPosition(left, top);
}

void Menu::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Down:
                if(_selected < _items.size() - 1) {
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
            default:
                _items[_selected]->onEvent(event);
        }
    }
}
