#pragma once

#include <ostream>
#include <board/position.h>
#include <astar/infosommet.h>
#include "element.h"

class Case : public InfoSommet<Sommet<Case>> {
    private:
        Position<> _position;
        Element* _element;

        void copy(const Case& c);
        void clear();

    public:
        Case(const Position<>& position, const Element* element);
        Case(const Case& c);
        ~Case();

        Case& operator = (const Case& c);

        /**
         * @brief Donne la position de la case
         * @return Position
         */
        inline Position<> position() const;

        /**
         * @brief Donne l'élément de la case, ou nullptr si la case est vide
         * @return Element
         */
        inline Element* element() const;

        /**
         * @brief Définit la nouvelle position de la case
         * @param position Nouvelle position
         */
        inline void setPosition(const Position<>& position);

        /**
         * @brief Définit l'élément de la case
         * @param element Nouvel élément, ou nullptr
         */
        void setElement(const Element* element);

        /**
         * @brief Fonction appelée quand un joueur physique passe sur la case
         * @param joueur Joueur
         */
        void heberge(Pacman& joueur);

        friend std::ostream& operator<<(std::ostream &, const Case&);

        operator std::string() const;
};

Position<> Case::position() const {
    return _position;
}

void Case::setPosition(const Position<>& position) {
    _position = position;
}

Element* Case::element() const {
    return _element;
}
