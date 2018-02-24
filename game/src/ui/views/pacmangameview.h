#pragma once

#include <game/pacmangame.h>
#include "gameview.h"

class PacmanGameView : public GameView {
    public:
        PacmanGameView(sf::RenderWindow* window, FenetreJeu* f, const SharedPtr<PacmanGame>& game);

        virtual void render(double timeElapsed) override;

        virtual void onEvent(const sf::Event& event) override;

        virtual void resize(const sf::Vector2f& size) override;

    private:
        /**
         * @brief Met à jour le texte du niveau
         */
        void updateLevelText();

        /**
         * @brief Met à jour la position du texte du niveau
         */
        void updateLevelPosition();

        sf::Text _level;
        SharedPtr<PacmanGame> _game;
};