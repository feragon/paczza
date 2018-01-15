#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include "boardview.h"
#include <cmath>

Boardview::Boardview(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f), _joueur(ResourceLoader::getSprite(Sprite::OPEN_PIZZA)) {

    _jeu = new Jeu(4);
}

void Boardview::resize(const sf::Vector2f& size) {
    for(unsigned int i = 0; i <= ceil(size.x / SPRITE_SIZE); i++) {
        for(unsigned int j = 0; j <= ceil(size.y / SPRITE_SIZE); j++) {

            sf::Sprite sprite(ResourceLoader::getSprite(Sprite::EMPTY_CELL));
            sprite.setPosition(i * SPRITE_SIZE, j * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }

    for(Sommet<Case>* sommet : _jeu->getGraphe()->sommets()) {
        sf::Sprite sprite(ResourceLoader::getSprite(Sprite::CELL));

        sprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        sprite.setPosition(sommet->position().x * SPRITE_SIZE, sommet->position().y * SPRITE_SIZE);
        _backgroundSprites.push_back(sprite);
    }

    for(Arete<Case, Chemin>* arete : _jeu->getGraphe()->aretes()) {
        sf::Sprite sprite(ResourceLoader::getSprite(Sprite::PATH));
        sf::Sprite sprite2(ResourceLoader::getSprite(Sprite::PATH));

        int s1_x = arete->sommet1()->position().x;
        int s1_y = arete->sommet1()->position().y;
        int s2_x = arete->sommet2()->position().x;
        int s2_y = arete->sommet2()->position().y;

        int angle = 0;

        if(s1_x < s2_x) {
            if(s1_y == s2_y) {
                angle = 90;
            }
            else {
                sprite.setTexture(ResourceLoader::getSprite(Sprite::DIAGONAL_PATH));
                sprite2.setTexture(ResourceLoader::getSprite(Sprite::DIAGONAL_PATH));
                if (s1_y < s2_y) {
                    angle = 90;
                }
            }
        }
        else if(s1_x == s2_x) {
            if(s1_y < s2_y ) {
                angle = 180;
            }
        }
        else { //s1_x > s2_x
            if(s1_y == s2_y) {
                angle = 270;
            }
            else {
                sprite.setTexture(ResourceLoader::getSprite(Sprite::DIAGONAL_PATH));
                sprite2.setTexture(ResourceLoader::getSprite(Sprite::DIAGONAL_PATH));
                if(s1_y < s2_y) {
                    angle = 180;
                }else {
                    angle = 270;
                }
            }
        }

        sprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        sprite.rotate(angle);
        sprite.setPosition(s1_x * SPRITE_SIZE, s1_y * SPRITE_SIZE);
        _backgroundSprites.push_back(sprite);


        sprite2.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        sprite2.rotate((angle + 180) % 360);
        sprite2.setPosition(s2_x * SPRITE_SIZE, s2_y * SPRITE_SIZE);
        _backgroundSprites.push_back(sprite2);
    }


}

void Boardview::render() {
    for(sf::Sprite sprite : _backgroundSprites) {
        _window->draw(sprite);
    }

    _joueur.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _joueur.setPosition(_jeu->getJoueur()->position().x * SPRITE_SIZE, _jeu->getJoueur()->position().y * SPRITE_SIZE);
    _window->draw(_joueur);
}

void Boardview::UpdatePlayer(int x, int y, int angle) {
    _jeu->getJoueur()->setPosition(Position(x, y));
    _joueur.setRotation(angle);
}

void Boardview::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Numpad2:
                UpdatePlayer(_jeu->getJoueur()->position().x, _jeu->getJoueur()->position().y+1, 270);
                break;

            case sf::Keyboard::Key::Numpad8:
                UpdatePlayer(_jeu->getJoueur()->position().x, _jeu->getJoueur()->position().y-1, 90);                break;

            case sf::Keyboard::Key::Numpad4:
                UpdatePlayer(_jeu->getJoueur()->position().x-1, _jeu->getJoueur()->position().y, 0);                break;

            case sf::Keyboard::Key::Numpad6:
                UpdatePlayer(_jeu->getJoueur()->position().x+1, _jeu->getJoueur()->position().y, 180);                break;
        }
    }
}