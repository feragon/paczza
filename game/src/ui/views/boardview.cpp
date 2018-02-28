#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <game/boardlistener.h>
#include <cmath>
#include "boardview.h"
#include <SFML/Audio.hpp>
#include <board/teleporter.h>
#include <board/point.h>
#include <board/teleporter.h>
#include <board/superpoint.h>

BoardView::BoardView(sf::RenderWindow* window, FenetreJeu* f, Board* board) :
        View(window, f) {

    _board = board;
    setFond(Sprite::EMPTY_CELL);
    _superPointId = 0;
}

void BoardView::genererSpritesElements() {
    for(Liste<Sommet<Case>>* l = _board->sommets(); l; l = l->next) {
        genererSpriteElement(l->value->contenu());
    }
}

void BoardView::genererSpriteElement(const Case& c) {
    _elements.erase(c.position());
    _animatedElements.erase(c.position());
    _sounds.erase(c.position());

    if(c.element()) {
        c.element()->accept(*this);
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

    for(std::pair<const Position<>, AnimatedSprite>& p : _animatedElements) {
        p.second.animate(timeElapsed);
        window()->draw(p.second);
    }
}

void BoardView::visite(const Point& point) {
    if(!point.position()) {
        return;
    }

    placeElement(point, sf::Sprite(ResourceLoader::getSprite(TOMATO_SMUDGE)));
    placeSound(point, EAT);
}

void BoardView::visite(const SuperPoint& superPoint) {
    if(!superPoint.position()) {
        return;
    }

    Sprite resource;
    _superPointId++;

    switch (_superPointId) {
        case 1:
            resource = CHEESE;
            break;

        case 2:
            resource = TOMATO;
            break;

        case 3:
            resource = HAM;
            break;

        case 4:
            resource = MUSHROOM;
            _superPointId = 0;
            break;

        default:
            resource = CHEESE;
            _superPointId = 0;
    }

    placeElement(superPoint, sf::Sprite(ResourceLoader::getSprite(resource)));
    placeSound(superPoint, BONUS);
}

void BoardView::visite(const Teleporter& teleporter) {
    if(!teleporter.position()) {
        return;
    }

    AnimatedSprite as(AnimatedSprite::ANIMATION_LINERAR, sf::Sprite(ResourceLoader::getSprite(TELEPORTER_1)), 4, true);
    as.addSprite(sf::Sprite(ResourceLoader::getSprite(TELEPORTER_2)));
    as.addSprite(sf::Sprite(ResourceLoader::getSprite(TELEPORTER_3)));

    placeElement(teleporter, as);
    placeSound(teleporter, TELEPORT);
}

void BoardView::placeElement(const Element& element, sf::Sprite sprite) {
    moveElement(element, sprite);
    _elements[element.position()->position()] = sprite;
}

void BoardView::placeElement(const Element& element, AnimatedSprite sprite) {
    moveElement(element, sprite);
    _animatedElements.insert(std::pair<Position<>, AnimatedSprite>(element.position()->position(), sprite));
}

void BoardView::moveElement(const Element& element, sf::Transformable& transformable) const {
    transformable.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    transformable.setPosition(element.position()->position().x * SPRITE_SIZE,
                              element.position()->position().y * SPRITE_SIZE);
}

void BoardView::placeSound(const Element& element, Sound sound) {
    _sounds.insert(std::pair<Position<>, Sound>(element.position()->position(), sound));
}
