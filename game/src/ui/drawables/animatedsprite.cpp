#include "animatedsprite.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include <iostream>

AnimatedSprite::AnimatedSprite(AnimatedSprite::AnimationType type, const sf::Sprite& base, double fps) {
    _type = type;
    _sprites.push_back(base);
    _fps = fps;

    reset();
}

void AnimatedSprite::addSprite(const sf::Sprite& sprite) {
    _sprites.push_back(sprite);
}

void AnimatedSprite::animate(double timeElapsed) {
    double framesAdded;

    if(_forward) {
        framesAdded = timeElapsed * _fps;
    }
    else {
        framesAdded = - timeElapsed * _fps;
    }

    switch (_type) {
        case ANIMATION_LINERAR:
            _frame = std::fmod(_frame + framesAdded, _sprites.size());
            break;

        case ANIMATION_CIRCULAR:
            _frame += std::fmod(framesAdded, _sprites.size());

            if(_frame < 0) {
                _forward = true;
                _frame = -_frame;
            }
            if(_frame > _sprites.size()) {
                _forward = false;
                _frame = _sprites.size() * 2 - _frame;
            }
            break;
    }
}

void AnimatedSprite::reset() {
    _forward = true;
    _frame = 0;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprites[(int) _frame], states);
}

void AnimatedSprite::setOrigin(double x, double y) {
    for(sf::Sprite& sprite : _sprites) {
        sprite.setOrigin(x, y);
    }
}

void AnimatedSprite::setPosition(double x, double y) {
    for(sf::Sprite& sprite : _sprites) {
        sprite.setPosition(x, y);
    }
}

void AnimatedSprite::setRotation(double angle) {
    for(sf::Sprite& sprite : _sprites) {
        sprite.setRotation(angle);
    }
}
