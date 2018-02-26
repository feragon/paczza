#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <game/boardlistener.h>
#include <cmath>
#include "boardview.h"
#include <SFML/Audio.hpp>

BoardView::BoardView(sf::RenderWindow* window, FenetreJeu* f, Board* board) :
        View(window, f) {

    _board = board;
    setFond(Sprite::EMPTY_CELL);
}

void BoardView::genererSpritesElements() {
    for(Liste<Sommet<Case>>* l = _board->sommets(); l; l = l->next) {
        genererSpriteElement(l->value->contenu());
    }
}

void BoardView::genererSpriteElement(const Case& c) {
    if(c.element()) {
        sf::Sprite sprite(ResourceLoader::getSprite(c.element()->sprite()));

        sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
        sprite.setPosition(c.position().x * SPRITE_SIZE,
                           c.position().y * SPRITE_SIZE);

        _elements[c.position()] = sprite;
    }
    else {
        _elements.erase(c.position());
    }
}

void BoardView::resize(const sf::Vector2f& size) {
    View::resize(size);

    for(Liste<Sommet<Case>>* sommet = _board->sommets(); sommet; sommet = sommet->next) {
        if(sommet->value->degre() > 0) {
            sf::Sprite sprite(ResourceLoader::getSprite(Sprite::CELL));

            sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
            sprite.setPosition(sommet->value->contenu().position().x * SPRITE_SIZE,
                               sommet->value->contenu().position().y * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }

    for(Liste<Arete<Chemin, Case>>* arete = _board->aretes(); arete; arete = arete->next) {

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
        sprite.setPosition((s1_x + vect_x/2) * SPRITE_SIZE, (s1_y + vect_y/2) * SPRITE_SIZE);
       _backgroundSprites.push_back(sprite);
    }

    genererSpritesElements();
}

void BoardView::render(double timeElapsed) {
    View::render(timeElapsed);

    for(const sf::Sprite& sprite : _backgroundSprites) {
        window()->draw(sprite);
    }

    for(const std::pair<const Position<>, sf::Sprite>& p : _elements) {
        window()->draw(p.second);
    }

    _elements[Position<>(6,1)].rotate(1);
    _elements[Position<>(6,8)].rotate(1);
}