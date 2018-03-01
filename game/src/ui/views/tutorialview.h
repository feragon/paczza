#pragma once

#include <ui/drawables/fog.h>
#include "view.h"
#include "boardview.h"
#include "gameview.h"

class TutorialView : public View, public ElementVisitor {
    public:
        /**
         * @brief Vue qui affiche le tutoriel
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         * @param game Jeu
         */
        TutorialView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game);
        virtual ~TutorialView();

        virtual void onEvent(const sf::Event& event) override;

        virtual void render(double timeElapsed) override;

        virtual void resize(const sf::Vector2f& size) override;

        /**
         * @brief Met à jour le tutoriel
         */
        void update();

        virtual void visite(const Point& point) override;

        virtual void visite(const SuperPoint& superPoint) override;

        virtual void visite(const Teleporter& teleporter) override;

    private:
        /**
         * @brief État du tutoriel
         */
        enum State {
            WELCOME,
            PACZZA_PRESENTATION,
            OBJECTIVE,
            MONSTERS,
            SUPER_POINTS,
            WEAK_MONSTERS,
            LIFES,
            SCORE,
            END
        };
        /**
         * @brief Centre un texte sur la fenêtre
         * @param text Texte
         * @param sprite Sprite
         */
        void center(sf::Text& text, sf::Sprite& sprite);

        GameView _gameView;
        State _state;
        bool _sendEvents;
        bool _showText;
        bool _superPointFound;


        sf::Text _indication;
        sf::Sprite _returnKey;
        Fog* _fog;

        CommandReceiver _commandReceiver;
};