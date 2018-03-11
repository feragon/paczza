#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <ui/drawables/multiplefonttext.h>
#include "view.h"

class Credits : public View {
    public:
        /**
         * @brief Vue des crédits
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         */
        Credits(sf::RenderWindow* window, FenetreJeu* f);

        virtual void render(double timeElapsed) override;
        virtual void resize(const sf::Vector2f& size) override;
        virtual void onEvent(const sf::Event& event) override;

        /**
         * @brief Change la vitesse de défilement
         * @param speed Nouvelle vitesse
         */
        void setSpeed(int speed);

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

        std::vector<MultipleFontText> _texts;
        float _position;
        int _speed;
        sf::Music _music;
};