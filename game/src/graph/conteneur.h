#pragma once

#include <sstream>
#include "identifiable.h"

template <class T>
class Conteneur : public Identifiable {
    private:
        T _contenu;

    public:
        /**
         * @brief Crée un conteneur
         * @param identifiant Identifiant du conteneur
         * @param contenu Contenu
         */
        Conteneur(int identifiant, const T& contenu);

        /**
         * @return Contenu
         */
        inline T& contenu();

        /**
         * @return Contenu
         */
        inline const T& contenu() const;

        /**
         * @brief Change le contenu
         * @param contenu Nouveau contenu
         */
        inline void setContenu(const T& contenu);

        operator std::string() const;

        template <class U>
        friend std::ostream& operator << (std::ostream& o, const Conteneur<U>& c);
};

template <class T>
Conteneur<T>::Conteneur(int identifiant, const T& contenu) :
    Identifiable(identifiant),
    _contenu(contenu) {

}

template <class T>
T& Conteneur<T>::contenu() {
    return _contenu;
}

template <class T>
const T& Conteneur<T>::contenu() const {
    return _contenu;
}

template <class T>
void Conteneur<T>::setContenu(const T& contenu) {
    _contenu = contenu;

}
template <class T>
Conteneur<T>::operator std::string() const {
    std::ostringstream oss;
    oss << "Conteneur(" << (std::string) ((Identifiable) *this) << "; contenu=" << _contenu << ")";

    return oss.str();
}

template <class T>
std::ostream& operator<<(std::ostream& o, const Conteneur<T>& c) {
    o << (std::string) c;
    return o;
}
