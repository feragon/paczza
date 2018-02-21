#pragma once

#include <game/player.h>
#include <graph/conteneur.h>
#include <sprite.h>
#include <sounds.h>
#include <game/pacman.h>
#include <SFML/Audio/Sound.hpp>

class Element {
    private:
        Sprite _sprite;
        Sound _sound;

    public:
        Element(Sprite sprite, Sound sound);

        /**
         * @brief Retourne le sprite associé à l'élément
         * @return Sprite
         */
        inline Sprite sprite() const;

        /**
         * @brief Définit le sprite
         * @param sprite Nouveau sprite
         */
        inline void setSprite(Sprite sprite);

        /**
        * @brief Retourne le son associé à l'élément
        * @return Sound
        */
        inline Sound sound() const;

        /**
        * @brief Définit le son
        * @param sound Nouveau son
        */
        inline void setSound(Sound sound);

        /**
         * @brief Fonction appelée lorsqu'un joueur passe sur la case
         * @param joueur Joueur concerné
         * @return Vrai si l'élément reste sur le plateau
         */
        virtual bool traversePar(Pacman& joueur) const = 0;

        /**
         * @brief Retourne une copie de l'élément
         * @return Coie de l'Element
         */
        virtual Element* clone() const = 0;

        /**
         * @brief Donne la représentation textuelle de l'élément
         * @return String
         */
        virtual std::string toString() const;

        operator std::string() const;

        friend std::ostream& operator << (std::ostream& o, const Element* element);
};

Sprite Element::sprite() const {
        return _sprite;
}

void Element::setSprite(Sprite sprite) {
        _sprite = sprite;
}

Sound Element::sound() const {
        return _sound;
}

void Element::setSound(Sound sound) {
        _sound = sound;
}