#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

class Fog : public sf::Drawable {
    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::RenderTexture _rt;

    public:
        /**
         * @brief Crée un élément de brouillard
         * @param size Taille de l'écran
         * @param position Centre du cercle visible
         */
        Fog(sf::Vector2f size, sf::Vector2f position);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};