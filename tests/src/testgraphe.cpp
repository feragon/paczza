#include <catch.hpp>
#include <graph/identifiable.h>
#include <graph/conteneur.h>
#include <graph/sommet.h>
#include <graph/arete.h>

TEST_CASE("Test Identifiable graphe") {
    Identifiable i(0);
    REQUIRE(i.cle() == 0);

    i.setCle(1);
    REQUIRE(i.cle() == 1);
    REQUIRE((std::string) i == "Identifiable(1)");
}

TEST_CASE("Test Conteneur graphe") {
    Conteneur<double> c(0, 1.5);
    REQUIRE(c.cle() == 0);
    REQUIRE(c.contenu() == 1.5);

    c.setContenu(2.5);
    REQUIRE(c.contenu() == 2.5);
    REQUIRE((std::string) c == "Conteneur(Identifiable(0); contenu=2.5)");
}

TEST_CASE("Test Sommet double graphe") {
    Sommet<double> sommet(0, 1.5);

    REQUIRE(sommet.cle() == 0);
    REQUIRE(sommet.degre() == 0);
    REQUIRE(sommet.contenu() == 1.5);

    sommet.setDegre(1);
    REQUIRE(sommet.degre() == 1);

    REQUIRE((std::string) sommet == "Sommet(Conteneur(Identifiable(0); contenu=1.5); degre=1)");
}

TEST_CASE("Test Sommet string graphe") {
    Sommet<std::string> sommet(1, "contenu");

    REQUIRE(sommet.cle() == 1);
    REQUIRE(sommet.degre() == 0);
    REQUIRE(sommet.contenu() == "contenu");

    sommet.setDegre(2);
    REQUIRE(sommet.degre() == 2);

    REQUIRE((std::string) sommet == "Sommet(Conteneur(Identifiable(1); contenu=contenu); degre=2)");
}

TEST_CASE("Test arete graphe") {
    Sommet<std::string> s1(0, "sommet 1");
    Sommet<std::string> s2(1, "sommet 1");

    {
        Arete<char, std::string> a(0, 'a', &s1, &s2);

        REQUIRE(a.cle() == 0);
        REQUIRE(a.contenu() == 'a');
        REQUIRE(a.debut() == &s1);
        REQUIRE(a.fin() == &s2);

        REQUIRE(s1.degre() == 1);
        REQUIRE(s2.degre() == 1);

        REQUIRE((std::string) a == "Arete(Conteneur(Identifiable(0); contenu=a); debut=0; fin=1)");
    }

    REQUIRE(s1.degre() == 0);
    REQUIRE(s2.degre() == 0);
}