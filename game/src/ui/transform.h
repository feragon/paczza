#pragma once

#include <SFML/System/Vector2.hpp>
#include <config.h>
#include <board/position.h>

template <typename T>
sf::Vector2<T> transform(const sf::Vector2<T>& position, const sf::Vector2f& origin = sf::Vector2f(0, 0)) {
    return sf::Vector2<T>(position.x * SPRITE_SIZE + origin.x, position.y * SPRITE_SIZE + origin.y);
};

template <typename T>
sf::Vector2<T> transform(const Position<T>& position, const sf::Vector2f& origin = sf::Vector2f(0, 0)) {
    return sf::Vector2<T>(position.x * SPRITE_SIZE + origin.x, position.y * SPRITE_SIZE + origin.y);
};