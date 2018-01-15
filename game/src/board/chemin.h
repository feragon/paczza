#pragma once

#include <ostream>

class Chemin {
    private:
        unsigned int _chaleur;

    public:
        Chemin(unsigned int chaleur);
        virtual ~Chemin();

        inline unsigned int chaleur();

        inline void setChaleur(unsigned int ch);

        friend std::ostream& operator<<(std::ostream &, const Chemin&);
};


unsigned int Chemin::chaleur() {
    return _chaleur;
}

void Chemin::setChaleur(unsigned int ch) {
    _chaleur = ch;
}