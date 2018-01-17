#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include "boardview.h"

Boardview::Boardview(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f), _joueur(ResourceLoader::getSprite(Sprite::OPEN_PIZZA)) {

    _jeu = new Jeu(4);
    setFond(Sprite::EMPTY_CELL);
}

void Boardview::resize(const sf::Vector2f& size) {
    View::resize(size);

    for(Sommet<Case>* sommet : _jeu->getGraphe()->sommets()) {
        if(sommet->degre() > 0) {
            sf::Sprite sprite(ResourceLoader::getSprite(Sprite::CELL));

            sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
            sprite.setPosition(sommet->position().x * SPRITE_SIZE, sommet->position().y * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }

    for(Arete<Case, Chemin>* arete : _jeu->getGraphe()->aretes()) {
        sf::Sprite sprite(ResourceLoader::getSprite(Sprite::PATH));

        int s1_x = arete->sommet1()->position().x;
        int s1_y = arete->sommet1()->position().y;

        //Vecteur S1->S2
        float vect_x = arete->sommet2()->position().x - arete->sommet1()->position().x;
        float vect_y = arete->sommet2()->position().y - arete->sommet1()->position().y;

        int angle = 0;

        if(vect_x == 1 || vect_x*vect_y > 0)
            angle = 90;

        if(vect_x != 0 && vect_y != 0)
            sprite.setTexture(ResourceLoader::getSprite(Sprite::DIAGONAL_PATH));

        sprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        sprite.setRotation(angle);
        sprite.setPosition((s1_x + vect_x/2) * SPRITE_SIZE, (s1_y + vect_y/2) * SPRITE_SIZE);
        _backgroundSprites.push_back(sprite);
    }
}

void Boardview::render() {
    View::render();

    for(sf::Sprite sprite : _backgroundSprites) {
        window()->draw(sprite);
    }

    _joueur.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _joueur.setPosition(_jeu->getJoueur()->position().x * SPRITE_SIZE, _jeu->getJoueur()->position().y * SPRITE_SIZE);
    window()->draw(_joueur);

    for(std::pair<Position,Sprite> p : _jeu->_aliments) {

        sf::Sprite sprite(ResourceLoader::getSprite(p.second));

        sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
        sprite.setPosition(p.first.x * SPRITE_SIZE, p.first.y * SPRITE_SIZE);
        window()->draw(sprite);
    }
}

void Boardview::UpdatePlayer(int x, int y, int angle) {

    for(Sommet<Case> * sommet :_jeu->getGraphe()->sommetsIncidents(_jeu->getGraphe()->sommet(_jeu->getJoueur()->position()))) {
        try {
            _joueur.setRotation(angle);
            if(sommet == _jeu->getGraphe()->sommet(Position(x,y)))
                _jeu->getJoueur()->setPosition(Position(x, y));
        }
        catch(std::invalid_argument ia) {}
    }

    for(std::pair<Position,Sprite> p : _jeu->_aliments) {
        if(p.first.x == x && p.first.y == y)
            _jeu->_aliments.erase(std::find(_jeu->_aliments.begin(),_jeu->_aliments.end(),p));
    }
}

void Boardview::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Numpad2:
                UpdatePlayer(_jeu->getJoueur()->position().x, _jeu->getJoueur()->position().y+1, 270);
                break;
            case sf::Keyboard::Key::Numpad8:
                UpdatePlayer(_jeu->getJoueur()->position().x, _jeu->getJoueur()->position().y-1, 90);
                break;
            case sf::Keyboard::Key::Numpad4:
                UpdatePlayer(_jeu->getJoueur()->position().x-1, _jeu->getJoueur()->position().y, 0);
                break;
            case sf::Keyboard::Key::Numpad6:
                UpdatePlayer(_jeu->getJoueur()->position().x+1, _jeu->getJoueur()->position().y, 180);
                break;
            case sf::Keyboard::Key::Numpad1:
                UpdatePlayer(_jeu->getJoueur()->position().x-1, _jeu->getJoueur()->position().y+1, 315);
                break;
            case sf::Keyboard::Key::Numpad3:
                UpdatePlayer(_jeu->getJoueur()->position().x+1, _jeu->getJoueur()->position().y+1, 225);
                break;
            case sf::Keyboard::Key::Numpad7:
                UpdatePlayer(_jeu->getJoueur()->position().x-1, _jeu->getJoueur()->position().y-1, 45);
                break;
            case sf::Keyboard::Key::Numpad9:
                UpdatePlayer(_jeu->getJoueur()->position().x+1, _jeu->getJoueur()->position().y-1, 135);
                break;
        }
    }
}