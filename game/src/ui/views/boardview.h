#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ui/fenetrejeu.h>
#include <game/jeu.h>
#include <game/joueur.h>
#include <ui/drawables/animatedsprite.h>
#include "view.h"

class Boardview : public View {
protected:
    ~Boardview();

public:
    Boardview(sf::RenderWindow* window, FenetreJeu* f);

    void resize(const sf::Vector2f& size) override;

    void render(double timeElapsed) override;

    virtual void onEvent(const sf::Event& event) override;

    void UpdatePlayer(int x, int y, int angle);

private:
    sf::Font _font;
    std::vector<sf::Sprite> _backgroundSprites;
    std::vector<sf::Text*> _texts;
    Jeu* _jeu;

    AnimatedSprite _joueur;
    sf::Text _score;
};