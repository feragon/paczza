#pragma once

#include <graph/conteneur.h>
#include <util/visitable.h>
#include "elementvisitor.h"
#include <board/case.h>

class Pacman;
class Element : public Visitable<ElementVisitor> {
    private:
        Case<Element>* _position;

    public:
        /**
         * @brief Crée un élément vide
         */
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
        inline Case<Element>* position() const;

        /**
         * @brief Définit la position de l'élément
         * @param position Nouvelle position
         */
        inline void setPosition(Case<Element>* position);

        /**
         * @brief Donne la représentation textuelle de l'élément
         * @return String
         */
        virtual std::string toString() const;

        operator std::string() const;

        friend std::ostream& operator << (std::ostream& o, const Element* element);
};

Case<Element>* Element::position() const {
        return _position;
}

void Element::setPosition(Case<Element>* position) {
        _position = position;
}
