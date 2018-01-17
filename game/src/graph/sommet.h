#pragma once

#include <ostream>
#include "position.h"

template <class S>
class Sommet {
    private:
        S* _donnees;
        int _degre;
        Position _position;

    public:
        Sommet(const Position& p, S* dataSommet);

        inline S* donnees();
        inline Position position();
        inline int degre();
        inline int setDegre(int i);

        template <class osS>
        friend std::ostream& operator<<(std::ostream& os, const Sommet<osS>& sommet);
};


template <class S>
Sommet<S>::Sommet(const Position& position, S* dataSommet) {
    _position = position;
    _donnees = dataSommet;
}

template <class S>
S* Sommet<S>::donnees() {
    return _donnees;
}

template <class S>
Position Sommet<S>::position() {
    return _position;
}

template <class S>
int Sommet<S>::degre() {
    return _degre;
}

template <class S>
int Sommet<S>::setDegre(int i) {
    _degre = i;
}

template <class S>
std::ostream& operator<<(std::ostream& os, const Sommet<S>& sommet) {
    os << "Sommet(_donnees: " << sommet._donnees << " _position: " << sommet._position << ")";
    return os;
}
