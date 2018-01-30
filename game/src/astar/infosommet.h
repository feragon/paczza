#pragma once

#include <astar/astart.h>

template <typename T>
class InfoSommet {
    public:
        InfoSommet();

        /**Sommet<InfoSommet>
         * @brief Donne l'état du sommet
         * @return État
         */
        inline int& etat();

        /**
         * @brief Donne le père du sommet
         * @return Père
         */
        T*& parent();

        double& c();

        double& h();

        double& g();

    private:
        int _etat;
        T* _parent;
        double _c;
        double _h;
        double _g;
};

template <typename T>
InfoSommet<T>::InfoSommet() {
    _etat = LIBRE;
    _parent = nullptr;
}

template <typename T>
int& InfoSommet<T>::etat() {
    return _etat;
}

template <typename T>
T*& InfoSommet<T>::parent() {
    return _parent;
}

template <typename T>
double& InfoSommet<T>::c() {
    return _c;
}

template <typename T>
double& InfoSommet<T>::h() {
    return _h;
}

template <typename T>
double& InfoSommet<T>::g() {
    return _g;
}
