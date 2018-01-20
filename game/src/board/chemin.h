#pragma once

#include <ostream>

class Chemin {
    private:
        double _chaleur;

    public:
        Chemin(double chaleur);
        virtual ~Chemin();

        /**
         * @brief Donne la chaleur du chemin
         * @return Chaleur
         */
        inline double chaleur() const;

        /**
         * @brief Définit la chaleur de chemin
         * @param ch Chaleur
         */
        inline void setChaleur(double chaleur);

        friend std::ostream& operator<<(std::ostream &, const Chemin&);
};


double Chemin::chaleur() const {
    return _chaleur;
}

void Chemin::setChaleur(double chaleur) {
    _chaleur = chaleur;
}