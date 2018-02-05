#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ui/fenetrejeu.h>
#include <game/jeu.h>
#include <game/player.h>
#include <ui/drawables/animatedsprite.h>
#include "view.h"
#include <game/onplayerpositionchanged.h>
#include <SFML/Audio/Sound.hpp>

class BoardView : public View, public OnPlayerPositionChanged {
    public:
        BoardView(sf::RenderWindow* window, FenetreJeu* f, Jeu* jeu);
        virtual ~BoardView();

        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        virtual void onEvent(const sf::Event& event) override;

        void onPlayerPositionChanged(const Position<>& oldPosition, const Position<>& newPosition) override;

        /**
         * @brief Donne le jeu associé à la vue
         * @return Jeu
         */
        inline Jeu* jeu();

    private:
        void genererSpritesElements();
        void genererSpriteElement(const Case& c);
        void generateLifesIndicator(const sf::Vector2f& windowSize);

        BoardView(const BoardView&);
        BoardView& operator = (const BoardView&);

        std::map<Position<>, sf::Sprite, cmpPosition<>> _elements;

        std::vector<sf::Sprite> _backgroundSprites;
        Jeu* _jeu;

        AnimatedSprite _joueur;
        sf::Text _score;

        std::map<Arete<Chemin, Case>*, sf::Sprite> _aretesMarquees;
};

Jeu* BoardView::jeu() {
    return _jeu;
}
