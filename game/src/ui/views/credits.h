#pragma once

#include <SFML/Graphics/Text.hpp>
#include "view.h"

class Credits : public View {
    public:
        Credits(sf::RenderWindow* window, FenetreJeu* f);

        virtual void render() override;
        virtual void resize(const sf::Vector2f& size) override;
        virtual void onEvent(const sf::Event& event) override;

    private:
        std::vector<sf::Text> _texts;
};