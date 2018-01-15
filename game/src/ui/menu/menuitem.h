#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

class MenuItem : public sf::Drawable {
    public:
        /**
         * @brief Donne la position de l'élément
         * @return Position
         */
        virtual sf::Vector2f position() const = 0;

        /**
         * @brief Donne les dimensions de l'élément
         * @return Dimensions
         */
        virtual sf::FloatRect bounds() const = 0;

        /**
         * @brief Change la position de l'élément
         * @param position Nouvelle position
         */
        virtual void setPosition(const sf::Vector2f& position) = 0;

        /**
         * @brief Fonction appelée lorsqu'un évenement arrive et que l'objet est sélectionné
         * @param event Evenement
         */
        virtual void onEvent(const sf::Event& event) = 0;

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    private:
        sf::Vector2i _position;
};