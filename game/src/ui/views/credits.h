#pragma once

#include <SFML/Graphics/Text.hpp>
#include "view.h"

class Credits : public View {
    public:
        Credits(sf::RenderWindow* window, FenetreJeu* f);

        virtual void render(double timeElapsed) override;
        virtual void resize(const sf::Vector2f& size) override;
        virtual void onEvent(const sf::Event& event) override;

    private:
        /**
         * @brief Déplace le texte
         * @param yOffest Positif pour monter, négatif pour descendre
         */
        void updateText(float yOffest);

        /**
         * @brief Crée le texte
         * @param initialYPosition Position verticale initiale
         */
        void createText(float initialYPosition);

        std::vector<sf::Text> _texts;
        float _position;
};