#pragma once

#include <ostream>

class Arete {
private:
    unsigned int _chaleur;

public:
    Arete(unsigned int chaleur);
    virtual ~Arete();

    inline unsigned int chaleur();

    inline void setChaleur(unsigned int ch);

    friend std::ostream& operator<<(std::ostream &, Arete const &);
};


unsigned int Arete::chaleur() {
    return _chaleur;
}

void Arete::setChaleur(unsigned int ch) {
    _chaleur = ch;
}