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
            LEFT_PINEAPPLE,
            UP_PINEAPPLE,
            RIGHT_PINEAPPLE,
            DOWN_PINEAPPLE,
            LEFT_PINEAPPLE_OFF,
            UP_PINEAPPLE_OFF,
            RIGHT_PINEAPPLE_OFF,
            DOWN_PINEAPPLE_OFF,
            PIZZA,
            OPEN_PIZZA,
            TOMATO_SMUDGE,
            FIN
        };

        static const sf::Texture& getSprite(Sprite s);

    private:
        std::map<Sprite, sf::Texture> _sprites;

        SpriteLoader();
        static SpriteLoader _instance;
};