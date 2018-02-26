#pragma once

#include <util/shared_ptr.h>
#include "boardview.h"

class GameView : public BoardView, public BoardListener {
    private:
        /**
         * @brief Met à jour les sprites des monstres
         */
        void updateMonsters();

        /**
         * @brief Affiche le joueur sur la fenêtre
         * @param timeElapsed Temps écoulé depuis le dernier dessin
         */
        void drawPlayer(double timeElapsed);

        /**
         * @brief Affiche les monstres sur la fenêtre
         * @param timeElapsed Temps écoulé depuis le dernier dessin
         */
        void drawMonsters(double timeElapsed);

        void generateLifesIndicator(const sf::Vector2f& windowSize);

        SharedPtr<Jeu> _game;
        sf::Text _score;

        AnimatedSprite _playerAnimatedSprite;
        std::map<const Monster*, AnimatedSprite> _monsters;

        std::map<Arete<Chemin, Case>*, sf::Sprite> _aretesMarquees;

    public:
        GameView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game);
        virtual ~GameView();

        virtual void render(double timeElapsed) override;

        /**
         * @brief Donne le jeu actuellement affiché
         * @return Jeu
         */
        inline SharedPtr<Jeu> game();

        /**
         * @brief Donne le sprite animé du joueur
         * @return AnimatedSprite
         */
        inline AnimatedSprite& playerAnimatedSprite();

        void playerMovementBegin(Pacman* player) override;
        void updateEdge(Arete<Chemin, Case>* edge) override;
        void updateVertice(Sommet<Case>* vertice) override;
        void onMonsterWeaknessUpdate(const Monster* monster) override;
        virtual void onNewTurn() override;
};

SharedPtr<Jeu> GameView::game() {
    return _game;
}

AnimatedSprite& GameView::playerAnimatedSprite() {
    return _playerAnimatedSprite;
}
