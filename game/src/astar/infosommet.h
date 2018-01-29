#pragma once

class InfoSommet {
    public:
        InfoSommet();

        enum Etat {
            LIBRE,
            OUVERT,
            FERME
        };

        /**
         * @brief Donne l'état du sommet
         * @return État
         */
        inline int& etat();

        /**
         * @brief Donne le père du sommet
         * @return Père
         */
        Sommet<InfoSommet>*& parent();

        double& c() const;

        double& h() const;

        double& g() const;

    private:
        int _etat;
        Sommet<InfoSommet>* _parent;
        double _c;
        double _h;
        double _g;
};

InfoSommet::InfoSommet() {
    _etat = LIBRE;
    _parent = nullptr;
}

int& InfoSommet::etat() {
    return _etat;
}

Sommet<InfoSommet>*& InfoSommet::parent() {
    return _parent;
}

double& InfoSommet::c() const {
    return _c;
}

double& InfoSommet::h() const {
    return _h;
}

double& InfoSommet::g() const {
    return _g;
}
