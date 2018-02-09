#pragma once

#include "boardview.h"

class GameView : public BoardView {
    private:
        void generateLifesIndicator(const sf::Vector2f& windowSize);

        Jeu* _game;
        sf::Text _score;

    public:
        GameView(sf::RenderWindow* window, FenetreJeu* f, Jeu* game);
        virtual ~GameView();

        virtual void render(double timeElapsed) override;

        virtual void onEvent(const sf::Event& event) override;

        /**
         * @brief Donne le jeu actuellement affiché
         * @return Jeu
         */
        inline Jeu* game();
};

Jeu* GameView::game() {
    return _game;
}
