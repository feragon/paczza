#include "view.h"
#include <cmath>
#include <config.h>
#include <ui/resourceloader.h>
#include <ui/transform.h>

View::View(sf::RenderWindow* window, FenetreJeu* f) {
    _window = window;
    _fenetreJeu = f;
}

View::~View() {

}

void View::resize(const sf::Vector2f& size) {
    if(_spriteFond == SPRITE_FIN) {
        return;
    }

    _fond.clear();

    for(unsigned int i = 0; i <= ceil(size.x / SPRITE_SIZE); i++) {
        for(unsigned int j = 0; j <= ceil(size.y / SPRITE_SIZE); j++) {
            sf::Sprite s(ResourceLoader::getSprite(_spriteFond));
            s.setPosition(transform(sf::Vector2f(i, j)));
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

void View::render(double timeElapsed) {
    for(sf::Sprite sprite : _fond) {
        _window->draw(sprite);
    }
}

void View::onEvent(const sf::Event& event) {
    try {
        manageEvent(event);
    }
    catch (UnknownCommand& e) {

    }
}
