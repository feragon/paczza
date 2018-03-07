#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
    public:
        /**
         * @brief Type de l'animation
         */
        enum AnimationType {
            ANIMATION_LINERAR,
            ANIMATION_CIRCULAR,
        };

        /**
         * @brief Crée un sprite animé
         * @param type Type d'animation
         * @param base Sprite de base
         * @param fps Nombre d'images par secondes
         * @param infinite Vrai si l'animation tourne en boucle
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

        /**
         * @return Vrai si l'animation tourne en boucle
         */
        inline bool infinite() const;

        /**
         * @brief Définit si l'animation tourne en boucle
         * @param infinite Vrai si l'animation doit tourner en boucle
         */
        inline void setInfinite(bool infinite);

        /**
         * @brief Donne l'image actuelle de l'animation
         * @return Indice de l'image
         */
        inline double frame() const;

        /**
         * @brief Définit l'image de l'animation
         * @param frame Nouvel indice
         */
        void setFrame(double frame);

        /**
         * @return Direction de l'animation
         */
        inline bool forward() const;

        /**
         * @brief Change la direction de l'animation
         * @param forward Nouvelle direction
         */
        inline void setForward(bool forward);

        /**
         * @brief Donne la taille et la position du sprite
         * @return sf::FloatRect
         */
        sf::FloatRect getGlobalBounds();

        /**
         * @brief Donne le nombre d'images par seconde de l'animation
         * @return Nombre d'images par seconde
         */
        inline double fps() const;

        /**
         * @brief Définit le nombre d'images par seconde
         * @param fps Nombre d'images par seconde
         */
        inline void setFps(double fps);

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

bool AnimatedSprite::infinite() const {
        return _infinite;
}

void AnimatedSprite::setInfinite(bool infinite) {
        _infinite = infinite;
}

double AnimatedSprite::frame() const {
        return _frame;
}

bool AnimatedSprite::forward() const {
    return _forward;
}

void AnimatedSprite::setForward(bool forward) {
    _forward = forward;
}

double AnimatedSprite::fps() const {
        return _fps;
}

void AnimatedSprite::setFps(double fps) {
        _fps = fps;
}
