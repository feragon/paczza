#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <sprite.h>

class FenetreJeu;

class View {
    public:
        virtual void render();

        /**
         * @brief Redimensionne la vue
         * @param size Nouvelles dimensions
         */
        virtual void resize(const sf::Vector2f& size);

        /**
         * @brief Function called when an event is received
         * @param event Event received
         */
        virtual void onEvent(const sf::Event& event) = 0;

        FenetreJeu* getFenetreJeu();

        /**
         * @brief Supprime le fond déjà crée
         */
        void clearFond();

        /**
         * @brief Définit le fond de la vue
         * @param sprite Sprite utilisé pour remplir la vue
         * @TODO: utiliser ça partout
         */
        void setFond(Sprite sprite);
    protected:
        View(sf::RenderWindow* window, FenetreJeu* f);
        sf::RenderWindow* _window;
        FenetreJeu * _fenetreJeu;

        Sprite _spriteFond;
        std::vector<sf::Sprite> _fond;
};