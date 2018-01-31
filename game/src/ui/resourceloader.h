#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <sprite.h>
#include <fonts.h>
#include <sounds.h>

class ResourceLoader {
    public:
        static const sf::Texture& getSprite(Sprite s);
        static const sf::Font& getFont(Font f);
        static const sf::SoundBuffer& getSound(Sound s);

    private:
        std::map<Sprite, sf::Texture> _sprites;
        std::map<Font, sf::Font> _fonts;
        std::map<Sound, sf::SoundBuffer> _sounds;

        ResourceLoader();

        /**
         * @brief Charge tous les sprites
         */
        void loadSprites();

        /**
         * @brief Charge toutes les polices de caractère
         */
        void loadFonts();

        /**
        * @brief Charge tous les sons
        */
        void loadSounds();

        static ResourceLoader _instance;
};