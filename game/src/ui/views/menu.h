#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include "view.h"

class Menu : public View {
    protected:
        Menu(sf::RenderWindow* window);
        ~Menu();

        /**
         * @brief Ajoute un élément au menu
         * @param title Texte de l'élément
         * @param callback Fonction appelée lors de la selection
         */
        void addMenu(const std::wstring& title, const std::function<void(void)>& callback);

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

        sf::Font _font;
        std::vector<sf::Sprite> _backgroundSprites;
        std::vector<sf::Text*> _texts;
        std::vector<std::function<void(void)>> _callbacks;
        sf::Sprite _selector;
        unsigned int _selected;
};