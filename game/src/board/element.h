#pragma once

#include <game/joueur.h>
#include <graph/conteneur.h>
#include <sprite.h>

class Element {
    private:
        Sprite _sprite;

    public:
        Element(Sprite sprite);

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
         * @brief Fonction appelée lorsqu'un joueur passe sur la case
         * @param joueur Joueur concerné
         * @return Vrai si l'élément reste sur le plateau
         */
        virtual bool traversePar(Joueur& joueur) const = 0;

        /**
         * @brief Retourne une copie de l'élément
         * @return Coie de l'Element
         */
        virtual Element* clone() const = 0;
};

Sprite Element::sprite() const {
        return _sprite;
}

void Element::setSprite(Sprite sprite) {
        _sprite = sprite;
}
