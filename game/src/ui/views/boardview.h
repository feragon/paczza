#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ui/fenetrejeu.h>
#include <game/jeu.h>
#include <game/player.h>
#include <ui/drawables/animatedsprite.h>
#include "view.h"
#include <game/gamelistener.h>
#include <SFML/Audio/Sound.hpp>
#include <ui/resourceloader.h>
#include <ui/transform.h>

template <typename ElementType>
class BoardView : public View {
    public:
        /**
         * @brief Vue du plateau
         * @param window Fenêtre SFML
         * @param f Fenêtre du jeu
         * @param board Plateau
         */
        BoardView(sf::RenderWindow* window, FenetreJeu* f, Board<ElementType>* board);

        void resize(const sf::Vector2f& size) override;

        void render(double timeElapsed) override;

        /**
         * @brief Donne le plateau associé à la vue
         * @return Board
         */
        inline Board<ElementType>* board();

    private:
        BoardView(const BoardView&);
        BoardView& operator = (const BoardView&);

        std::vector<sf::Sprite> _backgroundSprites;
        Board<ElementType>* _board;
};

template <typename ElementType>
Board<ElementType>* BoardView<ElementType>::board() {
    return _board;
}

template <typename ElementType>
BoardView<ElementType>::BoardView(sf::RenderWindow* window, FenetreJeu* f, Board<ElementType>* board) :
        View(window, f) {

    _board = board;
    setFond(Sprite::EMPTY_CELL);
}

template <typename ElementType>
void BoardView<ElementType>::resize(const sf::Vector2f& size) {
    _backgroundSprites.clear();
    
    View::resize(size);

    for(Liste<Sommet<Case<Element>>>* sommet = _board->sommets(); sommet; sommet = sommet->next) {
        if(sommet->value->degre() > 0) {
            sf::Sprite sprite(ResourceLoader::getSprite(Sprite::CELL));

            sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
            sprite.setPosition(transform<float>(sommet->value->contenu().position()));
            _backgroundSprites.push_back(sprite);
        }
    }

    for(Liste<Arete<Chemin, Case<Element>>>* arete = _board->aretes(); arete; arete = arete->next) {
        sf::Sprite sprite(ResourceLoader::getSprite(Sprite::PATH));

        int s1_x = arete->value->debut()->contenu().position().x;
        int s1_y = arete->value->debut()->contenu().position().y;

        //Vecteur S1->S2
        float vect_x = arete->value->fin()->contenu().position().x - arete->value->debut()->contenu().position().x;
        float vect_y = arete->value->fin()->contenu().position().y - arete->value->debut()->contenu().position().y;

        int angle = 0;

        if((vect_y == 0) || vect_x*vect_y > 0)
            angle = 90;

        if(vect_x != 0 && vect_y != 0)
            sprite.setTexture(ResourceLoader::getSprite(Sprite::DIAGONAL_PATH));

        if(!arete->value->contenu().estAccessible())
            sprite.setTexture(ResourceLoader::getSprite(Sprite::DOOR));

        sprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        sprite.setRotation(angle);
        sprite.setPosition(transform(sf::Vector2f(s1_x + vect_x/2, s1_y + vect_y/2)));
        _backgroundSprites.push_back(sprite);
    }
}

template <typename ElementType>
void BoardView<ElementType>::render(double timeElapsed) {
    View::render(timeElapsed);

    for(const sf::Sprite& sprite : _backgroundSprites) {
        window()->draw(sprite);
    }
}
