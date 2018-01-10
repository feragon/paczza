#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <ui/views/view.h>

class FenetreJeu {
    private:
        sf::RenderWindow _fenetre;
        View* _view;

        /**
         * @brief Redimensionne la vue
         * @param size Nouvelles dimensions
         */
        void resizeView(const sf::Vector2u& size);

    public:
        FenetreJeu();
        ~FenetreJeu();

        void ouvrir();
        void fermer();
};