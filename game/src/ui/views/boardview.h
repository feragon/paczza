#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ui/fenetrejeu.h>
#include <game/jeu.h>
#include "view.h"

class Boardview : public View {
protected:
    ~Boardview();

public:
    Boardview(sf::RenderWindow* window, FenetreJeu* f);

    void resize(const sf::Vector2f& size) override;

    void render() override;

    virtual void onEvent(const sf::Event& event) override;

private:
    sf::Font _font;
    std::vector<sf::Sprite> _backgroundSprites;
    std::vector<sf::Text*> _texts;
    sf::Sprite _selector;
    Jeu* _jeu;
};