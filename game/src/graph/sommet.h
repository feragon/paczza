#pragma once

#include <ostream>
#include "board/position.h"
#include "conteneur.h"

template <class T>
class Sommet : public Conteneur<T> {
    private:
        int _degre;

    public:
        /**
         * @brief Crée un nouveau sommet
         * @param identifiant Identifiant du sommet
         * @param contenu Contenu du sommet
         */
        Sommet(int identifiant, const T& contenu);

        /**
         * @return Degré du sommet
         */
        inline int degre() const;

        /**
         * @brief Change le degré du sommet
         * @param i Nouveau degré
         */
        inline void setDegre(int i);


        operator std::string() const;

        template <class osS>
        friend std::ostream& operator<<(std::ostream& os, const Sommet<osS>& sommet);
};

template <class T>
Sommet<T>::Sommet(int identifiant, const T& contenu) :
        Conteneur<T>(identifiant, contenu),
        _degre(0) {

}

template <class T>
int Sommet<T>::degre() const {
    return _degre;
}

template <class T>
void Sommet<T>::setDegre(int i) {
    _degre = i;
}

template <class T>
Sommet<T>::operator std::string() const {
    std::ostringstream oss;

    oss << "Sommet(" << (std::string) ((Conteneur<T>) *this) << "; degre=" << _degre << ")";

    return oss.str();
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Sommet<T>& sommet) {
    os << (std::string) sommet;
    return os;
}
