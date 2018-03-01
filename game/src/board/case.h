#pragma once

#include <ostream>
#include <board/position.h>
#include <astar/infosommet.h>
#include <graph/sommet.h>

template <typename ElementType>
class Case: public InfoSommet<Sommet<Case<ElementType>>> {
    private:
        Position<> _position;
        ElementType* _element;

        void copy(const Case& c);
        void clear();

    public:
        /**
         * @brief Crée une case
         * @param position Position de la case
         * @param element Element présent sur la case
         */
        Case(const Position<>& position, const ElementType* element);
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
        inline ElementType* element() const;

        /**
         * @brief Définit la nouvelle position de la case
         * @param position Nouvelle position
         */
        inline void setPosition(const Position<>& position);

        /**
         * @brief Définit l'élément de la case
         * @param element Nouvel élément, ou nullptr
         */
        void setElement(const ElementType* element);

        template <typename osElementType>
        friend std::ostream& operator<<(std::ostream &, const Case<osElementType>&);

        operator std::string() const;
};

template <typename ElementType>
Position<> Case<ElementType>::position() const {
    return _position;
}

template <typename ElementType>
void Case<ElementType>::setPosition(const Position<>& position) {
    _position = position;
}

template <typename ElementType>
ElementType* Case<ElementType>::element() const {
    return _element;
}

template <typename ElementType>
Case<ElementType>::Case(const Position<>& position, const ElementType* element) {
    _position = position;
    _element = nullptr;

    setElement(element);
}

template <typename ElementType>
Case<ElementType>::Case(const Case<ElementType>& c) : InfoSommet<Sommet<Case<ElementType>>>(c) {
    copy(c);
}

template <typename ElementType>
Case<ElementType>& Case<ElementType>::operator=(const Case& c) {
    clear();
    copy(c);

    return *this;
}

template <typename ElementType>
Case<ElementType>::~Case() {
    clear();
}

template <typename ElementType>
void Case<ElementType>::copy(const Case<ElementType>& c) {
    _position = c._position;

    if(c._element) {
        _element = c._element->clone();
    }
    else {
        _element = c._element;
    }
}

template <typename ElementType>
void Case<ElementType>::clear() {
    if(_element) {
        delete _element;
    }

    _element = nullptr;
}

template <typename ElementType>
std::ostream & operator<<(std::ostream &os, const Case<ElementType>& s) {
    os << "Case(" << s.position() << ")";
    return os;
}

template <typename ElementType>
Case<ElementType>::operator std::string() const {
    std::ostringstream oss;
    oss << (*this);
    return oss.str();
}

template <typename ElementType>
void Case<ElementType>::setElement(const ElementType* element) {
    if(_element) {
        delete _element;
    }

    if(element) {
        _element = element->clone();
        _element->setPosition(this);
    }
    else {
        _element = nullptr;
    }
}