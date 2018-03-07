#pragma once

#include <SFML/System/Vector2.hpp>
#include <config.h>

template <typename T, typename U>
sf::Vector2<T> transform(const sf::Vector2<T>& position, const sf::Vector2<U>& origin = sf::Vector2<U>(0, 0)) {
    return sf::Vector2<T>(position.x * SPRITE_SIZE + origin.x, position.y * SPRITE_SIZE + origin.y);
};