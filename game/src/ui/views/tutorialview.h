#pragma once

#include <ui/drawables/fog.h>
#include "view.h"
#include "boardview.h"
#include "gameview.h"

class TutorialView : public View {
    public:
        TutorialView(sf::RenderWindow* window, FenetreJeu* f);
        virtual ~TutorialView();

        virtual void onEvent(const sf::Event& event) override;

        virtual void render(double timeElapsed) override;

        virtual void resize(const sf::Vector2f& size) override;

    private:
        enum State {
            WELCOME,
            PACZZA_PRESENTATION,
            END
        };
        /**
         * @brief Centre un texte sur la fenêtre
         * @param text Texte
         * @param sprite Sprite
         */
        void center(sf::Text& text, sf::Sprite& sprite);

        /**
         * @brief Met à jour le tutoriel
         */
        void update();

        GameView _gameView;
        State _state;
        bool _sendEvents;
        bool _showText;


        sf::Text _indication;
        sf::Sprite _returnKey;
        Fog* _fog;
};