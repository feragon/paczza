#pragma once

#include <astar/etat.h>

template <typename T>
class InfoSommet {
    public:
        int etat;
        T* parent;
        double c;
        double h;
        double g;
};