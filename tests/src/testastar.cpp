#include <catch.hpp>
#include <game/astarfunctions.h>
#include <astar/astart.h>

TEST_CASE("AStar basique") {
    Graphe<Chemin, Case<Element>> g;
    auto s1 = g.creeSommet(Case<Element>(Position<>(0,0), nullptr));
    auto s2 = g.creeSommet(Case<Element>(Position<>(1,1), nullptr));
    g.creeArete(Chemin(), s1, s2);

    AStarFunctions::destination = s2;
    auto dest = AStarT<Graphe<Chemin, Case<Element>>, Sommet<Case<Element>>>::aStar(g, s1, &AStarFunctions::hh);

    REQUIRE(dest == s2);
}

TEST_CASE("AStar complexe") {
    Graphe<Chemin, Case<Element>> g;
    auto s1 = g.creeSommet(Case<Element>(Position<>(0,0), nullptr));
    auto s2 = g.creeSommet(Case<Element>(Position<>(2,0), nullptr));
    auto s3 = g.creeSommet(Case<Element>(Position<>(0,1), nullptr));
    auto s4 = g.creeSommet(Case<Element>(Position<>(1,1), nullptr));
    auto s5 = g.creeSommet(Case<Element>(Position<>(2,1), nullptr));
    g.creeArete(Chemin(), s1, s2);
    g.creeArete(Chemin(), s2, s5);

    g.creeArete(Chemin(), s1, s3);
    g.creeArete(Chemin(), s3, s4);
    g.creeArete(Chemin(), s4, s5);

    AStarFunctions::destination = s5;
    auto dest = AStarT<Graphe<Chemin, Case<Element>>, Sommet<Case<Element>>>::aStar(g, s1, &AStarFunctions::hh);

    REQUIRE(dest == s5);
    REQUIRE(s5->contenu().parent == s2);
    REQUIRE(s2->contenu().parent == s1);
}

TEST_CASE("AStar impossible") {
    Graphe<Chemin, Case<Element>> g;
    auto s1 = g.creeSommet(Case<Element>(Position<>(0,0), nullptr));
    auto s2 = g.creeSommet(Case<Element>(Position<>(1,1), nullptr));

    AStarFunctions::destination = s2;
    auto dest = AStarT<Graphe<Chemin, Case<Element>>, Sommet<Case<Element>>>::aStar(g, s1, &AStarFunctions::hh);

    REQUIRE(dest == nullptr);
}