#pragma once

#include <ostream>

class Sommet {
private:
    int _column;
    int _row;
    bool _tomatoSmudge;

public:
    Sommet(int colonne, int ligne);
    virtual ~Sommet();

    inline int column();
    inline int row();
    inline bool isTomatoSmudge();

    inline void eatTomatoSmudge();

    friend std::ostream& operator<<(std::ostream &, Sommet const &);
};

int Sommet::column() {
    return _column;
}
int Sommet::row() {
    return _row;
}
bool Sommet::isTomatoSmudge() {
    return _tomatoSmudge;
}

void Sommet::eatTomatoSmudge() {
    _tomatoSmudge = false;
}