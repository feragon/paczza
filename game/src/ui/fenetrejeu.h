#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <ui/views/view.h>
#include <graph/liste.h>

class FenetreJeu {
    private:
        sf::RenderWindow _fenetre;
        View* _view;
        Liste<View>* _historique;

        /**
         * @brief Redimensionne la vue
         * @param size Nouvelles dimensions
         */
        void resizeView(const sf::Vector2u& size);

    public:
        FenetreJeu();
        virtual ~FenetreJeu();

        void ouvrir();
        void fermer();

        void changerVue(View *v);

        /**
         * @brief Retourne à la vue précédente s'il y en a une et supprime l'actuelle
         */
        void vuePrecedente();
};