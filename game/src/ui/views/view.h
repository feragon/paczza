#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class View {
    public:
        virtual void render() = 0;

        /**
         * @brief Redimensionne la vue
         * @param size Nouvelles dimensions
         */
        virtual void resize(const sf::Vector2f& size) = 0;

    protected:
        View(sf::RenderWindow* window);
        sf::RenderWindow* _window;
};