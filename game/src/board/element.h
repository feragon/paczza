#pragma once

#include <game/player.h>
#include <graph/conteneur.h>
#include <sprite.h>
#include <sounds.h>
#include <game/pacman.h>
#include <SFML/Audio/Sound.hpp>
#include <util/visitable.h>
#include "elementvisitor.h"

class Element : public Visitable<ElementVisitor> {
    private:
        Case* _position;

    public:
        Element();

        /**
         * @brief Fonction appelée lorsqu'un joueur passe sur la case
         * @param joueur Joueur concerné
         * @return Vrai si l'élément reste sur le plateau
         */
        virtual bool traversePar(Pacman& joueur) const = 0;

        /**
         * @brief Retourne une copie de l'élément
         * @return Copie de l'Element
         */
        virtual Element* clone() const = 0;

        /**
         * @brief Donne la position de l'élément
         * @return Position
         */
        inline Case* position() const;

        /**
         * @brief Définit la position de l'élément
         * @param position Nouvelle position
         */
        inline void setPosition(Case* position);

        /**
         * @brief Donne la représentation textuelle de l'élément
         * @return String
         */
        virtual std::string toString() const;

        operator std::string() const;

        friend std::ostream& operator << (std::ostream& o, const Element* element);
};

Case* Element::position() const {
        return _position;
}

void Element::setPosition(Case* position) {
        _position = position;
}
