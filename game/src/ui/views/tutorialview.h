#pragma once

#include "view.h"
#include "boardview.h"

class TutorialView : public View {
    public:
        TutorialView(sf::RenderWindow* window, FenetreJeu* f);

        virtual void onEvent(const sf::Event& event) override;

        virtual void render(double timeElapsed) override;

        virtual void resize(const sf::Vector2f& size) override;

    private:
        BoardView _boardView;
};