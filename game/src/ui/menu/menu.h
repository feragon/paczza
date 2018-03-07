#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>
#include <ui/fenetrejeu.h>
#include <ui/command/commandreceiver.h>
#include "ui/views/view.h"
#include "menuitem.h"
#include "menumoveselector.h"

class Menu : public View {
    protected:
        /**
         * @brief Crée un menu
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         */
        Menu(sf::RenderWindow* window, FenetreJeu *f);
        virtual ~Menu();

        /**
         * @brief Ajoute un élément au menu
         * @param item Element à ajouter
         */
        void addItem(MenuItem* item);

    public:
        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        virtual void onEvent(const sf::Event& event) override;

        /**
         * @brief Met à jour la position du selecteur
         * @param offset Décalage
         */
        void updateSelector(long offset);
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