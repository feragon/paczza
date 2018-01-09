#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class View {
    public:
        virtual void render() = 0;

    protected:
        View(sf::RenderWindow* window);
        sf::RenderWindow* _window;
};