#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <game/boardlistener.h>
#include <cmath>
#include "boardview.h"
#include <SFML/Audio.hpp>

BoardView::BoardView(sf::RenderWindow* window, FenetreJeu* f, Board* board) :
        View(window, f),
        _joueur(AnimatedSprite::ANIMATION_CIRCULAR, sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_1)), 16, false) {


    _board = board;
    setFond(Sprite::EMPTY_CELL);

    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_2)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_3)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::PIZZA)));
    _joueur.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _joueur.setRotation(_board->player().direction() * 45);
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

    Position<> pos = _board->player().position()->contenu().position();
    double avancement = _board->player().avancement();
    double x = 0;
    double y = 0;
    Direction d = _board->player().direction();
    if(d == LEFT || d == LEFT_UP || d == LEFT_DOWN) {
        x = -1;
    }
    else if(d == RIGHT || d == RIGHT_DOWN || d == RIGHT_UP) {
        x = 1;
    }

    if(d == UP || d == LEFT_UP || d == RIGHT_UP) {
        y = -1;
    }
    else if(d == DOWN || d == LEFT_DOWN || d == RIGHT_DOWN) {
        y = 1;
    }

    _joueur.setRotation(_board->player().direction() * 45);
    _joueur.setPosition((pos.x + avancement * x) * SPRITE_SIZE, (pos.y + avancement * y) * SPRITE_SIZE);
    _joueur.animate(timeElapsed);
    window()->draw(_joueur);

    for(const std::pair<const Position<>, sf::Sprite>& p : _elements) {
        window()->draw(p.second);
    }

    double chaleurEnlevee = (UINT8_MAX / COOLDOWN_TIME) * timeElapsed;
    auto it = _aretesMarquees.begin();
    while (it != _aretesMarquees.end()) {
        Arete<Chemin, Case>* arete = it->first;
        double chaleur = arete->contenu().chaleur();

        if(chaleur <= chaleurEnlevee) {
            it = _aretesMarquees.erase(it++);
        }
        else {
            double nouvelleChaleur = chaleur - chaleurEnlevee;
            arete->contenu().setChaleur(nouvelleChaleur);
            it->second.setColor(sf::Color(255, 255, 255, (uint8_t) nouvelleChaleur));

            window()->draw(it->second);
            it++;
        }
    }

    for(Liste<Monster>* monstres = board()->monsters(); monstres; monstres = monstres->next) {
        sf::Sprite s(ResourceLoader::getSprite(RIGHT_PINEAPPLE));

        if(monstres->value->direction() == UP)
            s.setTexture(ResourceLoader::getSprite(UP_PINEAPPLE));
        if(monstres->value->direction() == LEFT)
            s.setTexture(ResourceLoader::getSprite(LEFT_PINEAPPLE));
        if(monstres->value->direction() == DOWN)
            s.setTexture(ResourceLoader::getSprite(DOWN_PINEAPPLE));

        s.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        Position<> monsterPos = monstres->value->position()->contenu().position();
        double avancement = monstres->value->avancement();
        double x = 0;
        double y = 0;
        Direction d = monstres->value->direction();
        if(d == LEFT || d == LEFT_UP || d == LEFT_DOWN) {
            x = -1;
        }
        else if(d == RIGHT || d == RIGHT_DOWN || d == RIGHT_UP) {
            x = 1;
        }

        if(d == UP || d == LEFT_UP || d == RIGHT_UP) {
            y = -1;
        }
        else if(d == DOWN || d == LEFT_DOWN || d == RIGHT_DOWN) {
            y = 1;
        }
        s.setPosition((monsterPos.x + avancement * x) * SPRITE_SIZE, (monsterPos.y + avancement * y) * SPRITE_SIZE); //TODO: optimiser
        window()->draw(s);
    }

    _elements[Position<>(6,1)].rotate(1);
    _elements[Position<>(6,8)].rotate(1);
}

void BoardView::updateEdge(Arete<Chemin, Case>* edge) {
    Position<> p1 = edge->debut()->contenu().position();
    Position<> p2 = edge->fin()->contenu().position();

    if(p1 == p2) {
        return;
    }

    Position<double> moveVect = p1 - p2;

    sf::Sprite sprite(ResourceLoader::getSprite(Sprite::COCAINE));

    sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    sprite.setPosition((p2.x + moveVect.x / 2) * SPRITE_SIZE,
                       (p2.y + moveVect.y / 2) * SPRITE_SIZE);

    _aretesMarquees[edge] = sprite;
}

void BoardView::updateVertice(Sommet<Case>* vertice) {
    genererSpriteElement(vertice->contenu());
}

void BoardView::playerMovementBegin(Pacman* player) {
    _joueur.reset();
}
