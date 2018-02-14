#pragma once

#include <util/shared_ptr.h>
#include "boardview.h"

class GameView : public BoardView {
    private:
        void generateLifesIndicator(const sf::Vector2f& windowSize);

        SharedPtr<Jeu> _game;
        sf::Text _score;

    public:
        GameView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game);
        virtual ~GameView();

        virtual void render(double timeElapsed) override;

        virtual void onEvent(const sf::Event& event) override;

        /**
         * @brief Donne le jeu actuellement affiché
         * @return Jeu
         */
        inline SharedPtr<Jeu> game();
};

SharedPtr<Jeu> GameView::game() {
    return _game;
}
