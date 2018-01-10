#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "view.h"

class Menu : public View {
    public:
        Menu(sf::RenderWindow* window);

        void resize(const sf::Vector2f& size) override;

    protected:
        /**
         * @brief Affiche le fond du menu dans la fenêtre
         */
        void renderBackground();

    private:
        std::vector<sf::Sprite> _backgroundSprites;
};