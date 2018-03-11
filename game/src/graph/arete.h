#pragma once

#include <ostream>

template <class S, class T>
class Arete : public Conteneur<S> {
    private:
        Sommet<T>* _debut;
        Sommet<T>* _fin;
    
    public:
        /**
         * @brief Crée une arête
         * @param clef Clé de l'arête
         * @param contenu Contenu
         * @param debut Sommet de début
         * @param fin Sommet de fin
         */
        Arete(int clef, const S& contenu, Sommet<T>* debut, Sommet<T>* fin);

        virtual ~Arete();

        /**
         * @return sommet de début
         */
        Sommet<T>* debut() const;

        /**
         * @return sommet de fin
         */
        Sommet<T>* fin() const;

        /**
         * @param s1 Sommet 1
         * @param s2 Sommet 2
         * @return Vrai si l'arête actuelle correspond aux deux sommets donnés
         */
        bool estEgal(const Sommet<T>* s1, const Sommet<T>* s2) const;

        operator std::string() const;
        template <class osS, class osT>
        friend std::ostream& operator<<(std::ostream& os, const Arete<osS, osT>& arete);
};


template <class S, class T>
Arete<S,T>::Arete(int clef, const S& contenu, Sommet<T>* debut, Sommet<T>* fin) :
    Conteneur<S>(clef, contenu){

    _debut = debut;
    _fin = fin;

    _debut->setDegre(_debut->degre() + 1);
    _fin->setDegre(_fin->degre() + 1);
}

template <class S, class T>
Arete<S,T>::~Arete() {
    _debut->setDegre(_debut->degre() - 1);
    _fin->setDegre(_fin->degre() - 1);
}

template <class S, class T>
Sommet<T>* Arete<S,T>::debut() const {
    return _debut;
}

template <class S, class T>
Sommet<T>* Arete<S,T>::fin() const {
    return _fin;
}

template <class S, class T>
bool Arete<S,T>::estEgal(const Sommet<T>* s1, const Sommet<T>* s2) const {
    return (s1 == _debut && s2 == _fin) || (s2 == _debut && s1 == _fin);
}

template <class S, class T>
Arete<S, T>::operator std::string() const {
    std::ostringstream oss;

    oss << "Arete(" << (std::string) ((Conteneur<S>) *this) <<
       "; debut=" << _debut->cle() <<
       "; fin=" << _fin->cle() <<
    ")";

    return oss.str();
}

template <class S, class T>
std::ostream& operator<<(std::ostream& o, const Arete<S,T>& arete) {
    o << (std::string) arete;
    return o;
}
