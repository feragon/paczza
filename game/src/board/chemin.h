#pragma once

#include <ostream>

class Chemin {
    private:
        double _chaleur;

    public:
        /**
         * @brief Crée un chemin
         * @param chaleur Chaleur du chemin
         */
        Chemin(double chaleur = 0);
        virtual ~Chemin();

        /**
         * @brief Donne la chaleur du chemin
         * @return Chaleur
         */
        inline double chaleur() const;

        /**
         * @brief Définit la chaleur de chemin
         * @param chaleur Chaleur
         */
        inline void setChaleur(double chaleur);

        /**
         * @return Vrai si le sommet est accessible par un joueur
         */
        bool estAccessible();

        friend std::ostream& operator<<(std::ostream &, const Chemin&);

        operator std::string() const;
};


double Chemin::chaleur() const {
    return _chaleur;
}

void Chemin::setChaleur(double chaleur) {
    _chaleur = chaleur;
}