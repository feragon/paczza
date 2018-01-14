#pragma once

#include <ostream>

class Sommet {
private:
    int _x;
    int _y;
    bool _tomatoSmudge;

public:
    Sommet(int x, int y);
    virtual ~Sommet();

    inline int x();
    inline int y();
    inline bool tomatoSmudge();

    inline void takeTomatoSmudge();

    friend std::ostream& operator<<(std::ostream &, Sommet const &);
};

int Sommet::x() {
    return _x;
}
int Sommet::y() {
    return _y;
}
bool Sommet::tomatoSmudge() {
    return _tomatoSmudge;
}

void Sommet::takeTomatoSmudge() {
    _tomatoSmudge = false;
}