#pragma once

template <typename Graphe, typename Sommet>
class AStarT {
    public:
        inline static Sommet* aStar(Graphe& graphe, Sommet* depart, double(*hh)(const Sommet* s));
};

template<typename Graphe, typename Sommet>
Sommet* AStarT<Graphe, Sommet>::aStar(Graphe& graphe, Sommet* depart, double (*hh)(const Sommet*)) {
    return nullptr;
}
