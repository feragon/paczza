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

        virtual void onEvent(const sf::Event& event) override;

    private:
        /**
         * @brief Center menu texts
         */
        void centerTexts();

        /**
         * @brief Update the selector icon position
         */
        void updateSelectorPosition();

        void launchGame();

        sf::Font _font;
        std::vector<sf::Sprite> _backgroundSprites;
        std::vector<sf::Text*> _texts;
        sf::Sprite _selector;
        unsigned int _selected;
};