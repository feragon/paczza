#pragma once

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include "menuitem.h"

class MenuButton : public MenuItem {
    public:
        MenuButton(const std::wstring& title, const std::function<void(void)>& callback);

        virtual sf::Vector2f position() const override;
        virtual sf::FloatRect bounds() const override;

        virtual void setPosition(const sf::Vector2f& position) override;

        virtual void onEvent(const sf::Event& event) override;

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Text _text;
        sf::Font _font;
        std::function<void(void)> _callback;
};