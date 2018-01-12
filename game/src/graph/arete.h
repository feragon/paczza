#pragma once

#include <ostream>

class Sommet;

class Arete {
private:
    Sommet *_extremite1;
    Sommet *_extremite2;
    int _chaleur;
public:
    Arete(Sommet &e1, Sommet &e2);
    virtual ~Arete();

    inline Sommet & e1();
    inline Sommet & e2();
    inline int chaleur();

    void setChaleur(int chaleur);

    friend std::ostream& operator<<(std::ostream &, Arete const &);
};

Sommet & Arete::e1() {
    return *_extremite1;
}
Sommet & Arete::e2() {
    return *_extremite2;
}
int Arete::chaleur() {
    return _chaleur;
}

