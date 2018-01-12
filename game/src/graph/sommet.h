#pragma once

#include <vector>
#include <ostream>

class Arete;

class Sommet {
private:
    int _x;
    int _y;
    bool _tomatoSmudge;
    std::vector<Arete*> _aretes_incid;
public:
    Sommet(int x, int y);
    virtual ~Sommet();

    inline int x();
    inline int y();
    inline bool tomatoSmudge();
    inline bool estIsole();

    void insererAreteAdj(Arete &a);
    std::vector<Arete*> incidentes();

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
bool Sommet::estIsole() {
    return _aretes_incid.empty();
}