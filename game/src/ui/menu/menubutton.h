#pragma once

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <ui/command/commandreceiver.h>
#include "menuitem.h"

class MenuButton : public MenuItem, public CommandReceiver {
    public:
        /**
         * @brief Crée un bouton de menu
         * @param title Texte du bouton
         * @param callback Action du bouton
         */
        MenuButton(const std::wstring& title, const std::function<void(void)>& callback);

        virtual sf::Vector2f position() const override;
        virtual sf::FloatRect bounds() const override;

        virtual void setPosition(const sf::Vector2f& position) override;

        virtual void onEvent(const sf::Event& event) override;

        /**
         * @brief Execute l'action du bouton
         */
        void executeCallback() const;

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Text _text;
        std::function<void(void)> _callback;
};