#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "view.h"

class MainMenu : public View {
    private:
        std::vector<sf::Sprite> _backgroundSprites;

    public:
        MainMenu(sf::RenderWindow* window);

        virtual void render() override;
};