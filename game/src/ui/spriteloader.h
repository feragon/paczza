#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>

class SpriteLoader {
    public:
        enum Sprite {
            EMPTY_CELL,
            CELL,
            PATH,
            DIAGONAL_PATH,
            CHEESE,
            TOMATO,
            HAM,
            MUSHROOM,
            PIZZA,
            OPEN_PIZZA,
            LEFT_PINEAPPLE,
            UP_PINEAPPLE,
            RIGHT_PINEAPPLE,
            DOWN_PINEAPPLE,
            TOMATO_SMUDGE,
            FIN
        };

        static const sf::Texture& getSprite(Sprite s);

    private:
        std::map<Sprite, sf::Texture> _sprites;

        SpriteLoader();
        static SpriteLoader _instance;
};