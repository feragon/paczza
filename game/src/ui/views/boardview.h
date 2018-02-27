#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ui/fenetrejeu.h>
#include <game/jeu.h>
#include <game/player.h>
#include <ui/drawables/animatedsprite.h>
#include "view.h"
#include <game/boardlistener.h>
#include <SFML/Audio/Sound.hpp>

class BoardView : public View {
    public:
        BoardView(sf::RenderWindow* window, FenetreJeu* f, Board* board);

        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        /**
         * @brief Donne le plateau associé à la vue
         * @return Board
         */
        inline Board* board();

    protected:
        void genererSpritesElements();
        void genererSpriteElement(const Case& c);

    private:
        BoardView(const BoardView&);
        BoardView& operator = (const BoardView&);

        std::map<Position<>, sf::Sprite, cmpPosition<>> _elements;
        std::map<Position<>, AnimatedSprite, cmpPosition<>> _animatedElements;

        std::vector<sf::Sprite> _backgroundSprites;
        Board* _board;
};

Board* BoardView::board() {
    return _board;
}