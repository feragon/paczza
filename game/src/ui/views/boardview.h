#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "view.h"

class Boardview : public View {
protected:
    Boardview(sf::RenderWindow* window);
    ~Boardview();

public:
    void resize(const sf::Vector2f& size) override;

    void render() override;

    virtual void onEvent(const sf::Event& event) override;

private:
    sf::Font _font;
    std::vector<sf::Sprite> _backgroundSprites;
    std::vector<sf::Text*> _texts;
    sf::Sprite _selector;
};