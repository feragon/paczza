#pragma once

#include <ostream>

class Chemin {
    private:
        unsigned int _chaleur;

    public:
        Chemin(unsigned int chaleur);
        virtual ~Chemin();

        /**
         * @brief Donne la chaleur du chemin
         * @return Chaleur
         */
        inline unsigned int chaleur();

        /**
         * @brief Définit la chaleur de chemin
         * @param ch Chaleur
         */
        inline void setChaleur(unsigned int chaleur);

        friend std::ostream& operator<<(std::ostream &, const Chemin&);
};


unsigned int Chemin::chaleur() {
    return _chaleur;
}

void Chemin::setChaleur(unsigned int chaleur) {
    _chaleur = chaleur;
}