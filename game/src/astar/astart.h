#pragma once

template <typename Graphe, typename Sommet>
class AStarT {
    public:
        static Sommet* aStar(Graphe& graphe, Sommet* depart, double(*hh)(const Sommet* s));
};