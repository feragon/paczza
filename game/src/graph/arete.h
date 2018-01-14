#pragma once

class Arete {
private:
    int _chaleur;

public:
    Arete(int chaleur);
    virtual ~Arete();

    inline int chaleur();
};


int Arete::chaleur() {
    return _chaleur;
}