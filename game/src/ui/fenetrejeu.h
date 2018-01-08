#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class FenetreJeu {
    private:
        sf::RenderWindow _fenetre;

    public:
        FenetreJeu();
        void ouvrir();
        void fermer();
};