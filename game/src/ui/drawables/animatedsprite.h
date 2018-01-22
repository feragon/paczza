#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class AnimatedSprite : public sf::Drawable {
    public:
        enum AnimationType {
            ANIMATION_LINERAR,
            ANIMATION_CIRCULAR,
        };

        /**
         * @brief Crée un sprite animé
         * @param type Type d'animation
         * @param base Sprite de base
         * @param fps Nombre d'images par secondes
         */
        AnimatedSprite(AnimationType type, const sf::Sprite& base, double fps, bool infinite);

        /**
         * @brief Ajoute une image à l'animation
         * @param sprite Image
         */
        void addSprite(const sf::Sprite& sprite);

        /**
         * @brief Avance l'animation
         * @param timeElapsed Temps écoulé en secondes depuis la dernière animation
         */
        void animate(double timeElapsed);

        /**
         * @brief Remet à zéro l'animation
         */
        void reset();

        //TODO: Refaire ça
        void setOrigin(double x, double y);
        void setPosition(double x, double y);
        void setRotation(double angle);
        sf::FloatRect getGlobalBounds();
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        double _fps;
        AnimationType _type;
        std::vector<sf::Sprite> _sprites;
        bool _forward;
        double _frame;
        bool _infinite;
};