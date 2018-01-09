#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <ui/views/view.h>

class FenetreJeu {
    private:
        sf::RenderWindow _fenetre;
        View* _view;

    public:
        FenetreJeu();
        ~FenetreJeu();

        void ouvrir();
        void fermer();
};