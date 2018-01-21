#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ui/fenetrejeu.h>
#include <game/jeu.h>
#include <game/player.h>
#include <ui/drawables/animatedsprite.h>
#include "view.h"

class BoardView : public View {
    public:
        BoardView(sf::RenderWindow* window, FenetreJeu* f);
        virtual ~BoardView();

        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        virtual void onEvent(const sf::Event& event) override;

        void updatePlayer(int x, int y, int angle);

    private:
        void genererSpritesElements();
        void genererSpriteElement(const Case& c);

        BoardView(const BoardView&);
        BoardView& operator = (const BoardView&);

        std::map<Position, sf::Sprite, cmpPosition> _elements;

        std::vector<sf::Sprite> _backgroundSprites;
        Jeu* _jeu;

        AnimatedSprite _joueur;
        sf::Text _score;

        std::map<Arete<Chemin, Case>*, sf::Sprite> _aretesMarquees;
};