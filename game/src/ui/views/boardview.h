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

class BoardView : public View, public ElementVisitor {
    public:
        BoardView(sf::RenderWindow* window, FenetreJeu* f, Board* board);

        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        /**
         * @brief Donne le plateau associé à la vue
         * @return Board
         */
        inline Board* board();

        virtual void visite(const Point& point) override;

        virtual void visite(const SuperPoint& superPoint) override;

        virtual void visite(const Teleporter& teleporter) override;

    protected:
        void genererSpritesElements();
        void genererSpriteElement(const Case& c);

        std::map<Position<>, Sound, cmpPosition<>> _sounds;

    private:
        BoardView(const BoardView&);
        BoardView& operator = (const BoardView&);

        void placeElement(const Element& element, sf::Sprite sprite);
        void placeElement(const Element& element, AnimatedSprite sprite);
        void moveElement(const Element& element, sf::Transformable& transformable) const;

        void placeSound(const Element& element, Sound sound);

        std::map<Position<>, sf::Sprite, cmpPosition<>> _elements;
        std::map<Position<>, AnimatedSprite, cmpPosition<>> _animatedElements;

        std::vector<sf::Sprite> _backgroundSprites;
        Board* _board;

        unsigned int _superPointId;
};

Board* BoardView::board() {
    return _board;
}