#pragma once

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