#pragma once

#include <ostream>

class Chemin {
    private:
        double _chaleur;

    public:
        Chemin(double chaleur = 0);
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