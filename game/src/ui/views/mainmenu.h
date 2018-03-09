#pragma once

#include "ui/menu/menu.h"
#include <game/jeu.h>

class MainMenu : public Menu {
    public:
        /**
         * @brief Crée le menu principal du jeu
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         */
        MainMenu(sf::RenderWindow* window, FenetreJeu* f);

    void render(double timeElapsed) override;

private:
        /**
         * @brief Action pour créer un nouveau jeu
         */
        void onNewGameSelected();

        /**
         * @brief Action pour afficher les crédits
         */
        void onCreditsSelected();

        /**
         * @brief Action pour quitter le jeu
         */
        void onExitSelected();

        /**
         * @brief Action pour afficher l'aide
         */
        void onHelpSelected();

        /**
         * @brief Crée un jeu avec tous les joueurs et les éléments
         * @return Jeu
         */
        SharedPtr<Jeu> generateGame();
        sf::Texture _titreTexture;
        sf::Sprite _titreSprite;
};