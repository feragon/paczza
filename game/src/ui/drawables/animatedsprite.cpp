#include "animatedsprite.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>
#include <iostream>

AnimatedSprite::AnimatedSprite(AnimatedSprite::AnimationType type, const sf::Sprite& base, double fps, bool infinite) {
    _type = type;
    _sprites.push_back(base);
    _fps = fps;
    _infinite = infinite;

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
            if(_infinite) {
                _frame = std::fmod(_frame + framesAdded, _sprites.size());
            }
            else {
                _frame = _frame + framesAdded;
                if(_frame >= _sprites.size()) {
                    _frame = _sprites.size() - 1;
                }
                else if(_frame < 0) {
                    _frame = 0;
                }
            }
            break;

        case ANIMATION_CIRCULAR:
            _frame += std::fmod(framesAdded, _sprites.size());

            if(_frame < 0) {
                if(_infinite) {
                    _forward = true;
                    _frame = -_frame;
                }
                else {
                    _frame = 0;
                }
            }
            if(_frame >= _sprites.size()) {
                _forward = false;
                _frame = _sprites.size() - fmod(_frame, _sprites.size());
            }
            break;
    }
}

void AnimatedSprite::reset() {
    _forward = true;
    _frame = 0;
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(_sprites[(int) _frame], states);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() {
    return _sprites.front().getGlobalBounds();
}

void AnimatedSprite::setFrame(double frame) {
    if(frame < 0 || frame >= _sprites.size()) {
        throw std::runtime_error("Indice d'image invalide");
    }
    _frame = frame;
}
