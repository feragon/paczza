#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include "ui/views/view.h"
#include "menuitem.h"

class Menu : public View {
    protected:
        Menu(sf::RenderWindow* window);
        virtual ~Menu();

        /**
         * @brief Ajoute un élément au menu
         * @param item Element à ajouter
         */
        void addItem(MenuItem* item);

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

        std::vector<sf::Sprite> _backgroundSprites;
        std::vector<MenuItem*> _items;
        sf::Sprite _selector;
        unsigned int _selected;
};