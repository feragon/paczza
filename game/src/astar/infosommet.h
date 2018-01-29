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
        inline Etat& etat();

        /**
         * @brief Définit l'état du sommet
         * @param etat nouvel état
         */
        inline void setEtat(Etat etat);

    private:
        Etat _etat;
};

InfoSommet::Etat& InfoSommet::etat() {
    return _etat;
}

void InfoSommet::setEtat(InfoSommet::Etat etat) {
    _etat = etat;
}
