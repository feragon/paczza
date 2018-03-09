#pragma once

#include <util/shared_ptr.h>
#include "boardview.h"

class GameView : public BoardView<Element>, public GameListener, public ElementVisitor {
    private:
        /**
         * @brief Met à jour les sprites des monstres
         */
        void updateMonsters();

        /**
         * @brief Met à jour le sprite du joueur
         */
        void updatePlayer();

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

        /**
         * @brief Génère les sprites de nombre de vies
         * @param windowSize Taille de la fenêtre
         */
        void generateLifesIndicator(const sf::Vector2f& windowSize);

        /**
         * @brief Ajoute un sprite représentant un élément
         * @param element Element représenté
         * @param sprite Sprite
         */
        void placeElement(const Element& element, sf::Sprite sprite);

        /**
         * @brief Ajoute un sprite animé représentant un élément
         * @param element Element représenté
         * @param sprite Sprite
         */
        void placeElement(const Element& element, AnimatedSprite sprite);

        /**
         * @brief Place un sprite représentant un élément
         * @param element Element représenté
         * @param transformable Sprite
         */
        void moveElement(const Element& element, sf::Transformable& transformable) const;

        /**
         * @brief Ajoute un son qui sera joué lorsque le joueur touche un élément
         * @param element Element concerné
         * @param sound Son
         */
        void placeSound(const Element& element, Sound sound);

        unsigned int _superPointId;

        SharedPtr<Jeu> _game;
        sf::Text _score;

        sf::Sound _sound;

        AnimatedSprite _playerAnimatedSprite;
        std::map<const Monster*, AnimatedSprite> _monsters;

        std::map<Arete<Chemin, Case<Element>>*, sf::Sprite> _aretesMarquees;

        std::map<Position<>, sf::Sprite, cmpPosition<>> _elements;
        std::map<Position<>, AnimatedSprite, cmpPosition<>> _animatedElements;
        std::unordered_map<Position<>, Sound> _sounds;
        std::vector<sf::Sprite> _lifes;

    protected:
        /**
         * @brief Met à jour les sprites de tous les éléments
         */
        void genererSpritesElements();

        /**
         * @brief Met à jour le sprite de l'élément sur la case donnée
         * @param c Case
         */
        void genererSpriteElement(const Case<Element>& c);

    public:
        /**
         * @brief Vue du jeu
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         * @param game Jeu à afficher
         */
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

        /**
         * @brief Donne les sprites animés des monstres
         * @return AnimatedSprites
         */
        inline std::map<const Monster*, AnimatedSprite>& monsterAnimatedSprites();

        void playerMovementBegin(Pacman* player) override;
        void updateEdge(Arete<Chemin, Case<Element>>* edge) override;
        void updateVertice(Sommet<Case<Element>>* vertice) override;
        void onMonsterWeaknessUpdate(const Monster* monster) override;
        virtual void onNewTurn() override;

        virtual void visite(const Point& point) override;
        virtual void visite(const SuperPoint& superPoint) override;
        virtual void visite(const Teleporter& teleporter) override;

        virtual void resize(const sf::Vector2f& size) override;

        /**
         * @brief Démarre la partie
         */
        virtual void startGame();
};

SharedPtr<Jeu> GameView::game() {
    return _game;
}

AnimatedSprite& GameView::playerAnimatedSprite() {
    return _playerAnimatedSprite;
}

std::map<const Monster*, AnimatedSprite>& GameView::monsterAnimatedSprites() {
    return _monsters;
}
