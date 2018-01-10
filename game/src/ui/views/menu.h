#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "view.h"

class Menu : public View {
    protected:
        Menu(sf::RenderWindow* window);
        ~Menu();

        void addMenu(const std::wstring& title);

    public:
        void resize(const sf::Vector2f& size) override;

        void render() override;

    private:
        void centerTexts();

        sf::Font _font;
        std::vector<sf::Sprite> _backgroundSprites;
        std::vector<sf::Text*> _texts;
};