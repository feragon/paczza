#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <sprite.h>
#include <SFML/Graphics/Font.hpp>
#include <fonts.h>

class ResourceLoader {
    public:
        static const sf::Texture& getSprite(Sprite s);
        static const sf::Font& getFont(Font f);

    private:
        std::map<Sprite, sf::Texture> _sprites;
        std::map<Font, sf::Font> _fonts;

        ResourceLoader();

        /**
         * @brief Charge tous les sprites
         */
        void loadSprites();

        /**
         * @brief Charge toutes les polices de caractère
         */
        void loadFonts();

        static ResourceLoader _instance;
};