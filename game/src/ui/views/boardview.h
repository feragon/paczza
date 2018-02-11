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

class BoardView : public View, public BoardListener {
    public:
        BoardView(sf::RenderWindow* window, FenetreJeu* f, Board* board);

        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        void playerMovementBegin(Pacman* player) override;
        void updateEdge(Arete<Chemin, Case>* edge) override;
        void updateVertice(Sommet<Case>* vertice) override;

        /**
         * @brief Donne le plateau associé à la vue
         * @return Board
         */
        inline Board* board();

    private:
        void genererSpritesElements();
        void genererSpriteElement(const Case& c);

        BoardView(const BoardView&);
        BoardView& operator = (const BoardView&);

        std::map<Position<>, sf::Sprite, cmpPosition<>> _elements;

        std::vector<sf::Sprite> _backgroundSprites;
        Board* _board;

        AnimatedSprite _joueur;

        std::map<Arete<Chemin, Case>*, sf::Sprite> _aretesMarquees;
};

Board* BoardView::board() {
    return _board;
}