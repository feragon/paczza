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
        /**
         * @param s Nom du sprite
         * @return Sprite
         */
        static const sf::Texture& getSprite(Sprite s);

        /**
         * @param f Nom de la police de caractère
         * @return Police de caractère
         */
        static const sf::Font& getFont(Font f);

        /**
         * @param s Nom du son
         * @return Son
         */
        static const sf::SoundBuffer& getSound(Sound s);

    private:
        std::map<Sprite, sf::Texture> _sprites;
        std::map<Font, sf::Font> _fonts;
        std::map<Sound, sf::SoundBuffer> _sounds;

        /**
         * @brief Crée le gestionnaire de resources
         */
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