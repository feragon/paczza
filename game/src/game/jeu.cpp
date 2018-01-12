#include <iostream>
#include "jeu.h"

Jeu::Jeu(unsigned short nbMonstres) :
    _graphe(5,5) {

    std::vector<Sommet*> sommets = _graphe.sommets();
    std::vector<Arete*> aretes = _graphe.aretes();

    std::vector<Arete*>::const_iterator it;
    for (it = aretes.begin(); it != aretes.end(); it++)
        std::cout << (**it);
}
