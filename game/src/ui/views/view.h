#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <sprite.h>
#include <ui/command/commandreceiver.h>

class FenetreJeu;

class View : public CommandReceiver {
    public:
        virtual ~View();

        /**
         * @brief Donne la fenre SFML
         * @return Fenêtre SFML
         */
        inline sf::RenderWindow* window();

        /**
         * @brief Donne la fenêtre du jeu
         * @return Fenêtre du jeu
         */
        inline FenetreJeu* fenetreJeu();

        /**
         * @brief Définit le fond de la vue
         * @param sprite Sprite utilisé pour remplir la vue
         */
        void setFond(Sprite sprite);

        /**
         * @brief Provoque le rendu de la vue
         * @param timeElapsed Temps écoulé depuis le dernier rendu
         */
        virtual void render(double timeElapsed);

        /**
         * @brief Redimensionne la vue
         * @param size Nouvelles dimensions
         */
        virtual void resize(const sf::Vector2f& size);

        /**
         * @brief Function called when an event is received
         * @param event Event received
         */
        virtual void onEvent(const sf::Event& event);

        /**
         * @brief Supprime le fond déjà crée
         */
        void clearFond();

    protected:
        /**
         * @brief Crée une vue
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         */
        View(sf::RenderWindow* window, FenetreJeu* f);

    private:
        sf::RenderWindow* _window;
        FenetreJeu * _fenetreJeu;

        Sprite _spriteFond;
        std::vector<sf::Sprite> _fond;
};

FenetreJeu* View::fenetreJeu() {
    return _fenetreJeu;
}

sf::RenderWindow* View::window() {
    return _window;
}
