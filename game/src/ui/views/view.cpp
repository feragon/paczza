#include "view.h"
#include <cmath>
#include <config.h>
#include <ui/resourceloader.h>

View::View(sf::RenderWindow* window, FenetreJeu* f) {
    _window = window;
    _fenetreJeu = f;
}

void View::resize(const sf::Vector2f& size) {
    if(_spriteFond == SPRITE_FIN) {
        return;
    }

    for(unsigned int i = 0; i <= ceil(size.x / SPRITE_SIZE); i++) {
        for(unsigned int j = 0; j <= ceil(size.y / SPRITE_SIZE); j++) {
            sf::Sprite s(ResourceLoader::getSprite(_spriteFond));
            s.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
            _fond.push_back(s);
        }
    }
}

void View::setFond(Sprite sprite) {
    _spriteFond = sprite;
    resize(_window->getView().getSize());
}

void View::clearFond() {
    _spriteFond = SPRITE_FIN;
    _fond.clear();
}

void View::render() {
    for(sf::Sprite sprite : _fond) {
        _window->draw(sprite);
    }
}