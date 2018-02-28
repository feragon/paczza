#include "fog.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <config.h>

Fog::Fog(sf::Vector2f size, sf::Vector2f position) {
    sf::CircleShape cs(SPRITE_SIZE);
    cs.setFillColor(sf::Color(50,50,50,50));
    cs.setOrigin(SPRITE_SIZE, SPRITE_SIZE);
    cs.setPosition(sf::Vector2f(position.x, size.y - position.y));

    _rt.create(size.x, size.y, false);
    _rt.clear(sf::Color(255, 255, 255, 128));

    sf::RenderStates rs;
    rs.blendMode = sf::BlendNone;
    _rt.draw(cs, rs);

    _texture = _rt.getTexture();
    _sprite = sf::Sprite(_texture);
}

void Fog::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
