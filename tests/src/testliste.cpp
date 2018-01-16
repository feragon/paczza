#include <catch.hpp>
#include <graph/liste.h>

TEST_CASE("Test creation liste") {
    double a = 0;
    double b = 1;
    double c = 2;

    Liste<double>* l = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    REQUIRE(Liste<double>::taille(l) == 3);

    REQUIRE(l->value == &a);
    REQUIRE(l->next->value == &b);
    REQUIRE(l->next->next->value == &c);
}

TEST_CASE("Test taille liste") {
    REQUIRE(Liste<double>::taille(nullptr) == 0);

    double a = 0;
    double b = 1;
    double c = 2;

    Liste<double>* l = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    REQUIRE(Liste<double>::taille(l) == 3);
    REQUIRE(Liste<double>::taille(l->next) == 2);
    REQUIRE(Liste<double>::taille(l->next->next) == 1);
}

TEST_CASE("Test toString liste") {
    REQUIRE(Liste<double>::toString(nullptr) == "()");

    double a = 0;
    double b = 1;
    double c = 2;

    Liste<double>* l = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    REQUIRE(Liste<double>::toString(l) == "(0, 1, 2)");
    REQUIRE(Liste<double>::toString(l, "[", "; ", "]") == "[0; 1; 2]");
}

bool estPlusPetitDouble(const double* a, const double* b) {
    return *a <= *b;
}

TEST_CASE("Test insertion ordonnée liste") {
    double a = 0;
    double b = 1;
    double c = 2;
    double i1 = 0;
    double i2 = -1;
    double i3 = 1.5;

    Liste<double>* l1 = nullptr;
    Liste<double>* l2 = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    Liste<double>* l3 = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));

    Liste<double>::insertionOrdonnee(&i1, l1, estPlusPetitDouble);
    Liste<double>::insertionOrdonnee(&i2, l2, estPlusPetitDouble);
    Liste<double>::insertionOrdonnee(&i3, l3, estPlusPetitDouble);

    REQUIRE(Liste<double>::toString(l1) == "(0)");
    REQUIRE(Liste<double>::toString(l2) == "(-1, 0, 1, 2)");
    REQUIRE(Liste<double>::toString(l3) == "(0, 1, 1.5, 2)");
}

TEST_CASE("Test dépiler liste") {
    double a = 0;
    double b = 1;
    double c = 2;

    Liste<double>* l = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    Liste<double>* l2 = nullptr;

    try {
        Liste<double>::depiler(l2);
        REQUIRE(false);
    }
    catch (std::invalid_argument) {

    }

    REQUIRE(Liste<double>::depiler(l) == &a);
    REQUIRE(Liste<double>::taille(l) == 2);

    REQUIRE(Liste<double>::depiler(l) == &b);
    REQUIRE(Liste<double>::taille(l) == 1);

    REQUIRE(Liste<double>::depiler(l) == &c);
    REQUIRE(Liste<double>::taille(l) == 0);

}

TEST_CASE("Test retire liste") {
    double a = 0;
    double b = 1;
    double c = 2;
    double d = 2;

    Liste<double>* l = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    Liste<double>* l2 = nullptr;

    REQUIRE(!Liste<double>::retire(nullptr, l2));

    REQUIRE(!Liste<double>::retire(&d, l));
    REQUIRE(Liste<double>::taille(l) == 3);

    REQUIRE(Liste<double>::retire(&b, l));
    REQUIRE(Liste<double>::toString(l) == "(0, 2)");
}

TEST_CASE("Test efface1 liste") {
    double a = 0;
    double b = 1;
    double c = 2;

    Liste<double>* l = new Liste<double>(&a, new Liste<double>(&b, new Liste<double>(&c)));
    Liste<double>* l2 = nullptr;

    Liste<double>::efface1(l2);
    Liste<double>::efface1(l);

    REQUIRE(Liste<double>::taille(l) == 0);
    REQUIRE(Liste<double>::taille(l2) == 0);
}

TEST_CASE("Test efface2 liste") {
    double* a = new double(0);
    double* b = new double(1);
    double* c = new double(2);

    Liste<double>* l = new Liste<double>(a, new Liste<double>(b, new Liste<double>(c)));
    Liste<double>* l2 = nullptr;

    Liste<double>::efface2(l2);
    Liste<double>::efface2(l);

    REQUIRE(Liste<double>::taille(l) == 0);
    REQUIRE(Liste<double>::taille(l2) == 0);
}

TEST_CASE("Test copie1 liste") {
    double* a = new double(0);
    double* b = new double(1);
    double* c = new double(2);

    Liste<double>* l = new Liste<double>(a, new Liste<double>(b, new Liste<double>(c)));
    Liste<double>* l2 = Liste<double>::copie1(l);

    *a = 1;
    *b = 2;
    *c = 3;

    REQUIRE(Liste<double>::toString(l2) == "(1, 2, 3)");
}

TEST_CASE("Test copie2 liste") {
    double* a = new double(0);
    double* b = new double(1);
    double* c = new double(2);

    Liste<double>* l = new Liste<double>(a, new Liste<double>(b, new Liste<double>(c)));
    Liste<double>* l2 = Liste<double>::copie2(l);

    *a = 1;
    *b = 2;
    *c = 3;

    REQUIRE(Liste<double>::toString(l) == "(1, 2, 3)");
    REQUIRE(Liste<double>::toString(l2) == "(0, 1, 2)");
}

class Copie3 {
    public:
        bool value;

        Copie3(bool v) {
            value = v;
        }

        Copie3* copie() {
            return new Copie3(value);
        };
};

TEST_CASE("Test copie3 liste") {
    Copie3 c1(false);
    Copie3 c2(true);

    Liste<Copie3>* l = new Liste<Copie3>(&c1, new Liste<Copie3>(&c2));
    Liste<Copie3>* l2 = Liste<Copie3>::copie3(l);

    c1 = Copie3(true);
    c2 = Copie3(false);

    bool r1 = l->value->value && !(l->next->value->value);
    bool r2 = !(l2->value->value) && l2->next->value->value;
    REQUIRE(r1);
    REQUIRE(r2);
}

TEST_CASE("Test appartient liste") {
    double* a = new double(0);
    double* b = new double(1);
    double* c = new double(2);

    Liste<double>* l = new Liste<double>(a, new Liste<double>(b, new Liste<double>(c)));

    REQUIRE(Liste<double>::appartient(nullptr, l) == nullptr);
    REQUIRE(Liste<double>::appartient(b, l) == l->next);
}

class Appartient {
    public:
        bool operator() (const double* T) const {
            return (*T) == 2;
        }
};

TEST_CASE("Test appartient foncteur liste") {
    double* a = new double(0);
    double* b = new double(1);
    double* c = new double(2);

    Liste<double>* l = new Liste<double>(a, new Liste<double>(b, new Liste<double>(c)));

    Appartient appartient;

    REQUIRE(Liste<double>::appartient<Appartient>(nullptr, appartient) == nullptr);
    REQUIRE(Liste<double>::appartient<Appartient>(l, appartient) == l->next->next);
}