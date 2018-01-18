#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include "boardview.h"

Boardview::Boardview(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f),
        _joueur(AnimatedSprite::ANIMATION_CIRCULAR, sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_1)), 16) {

    _jeu = new Jeu(4);
    setFond(Sprite::EMPTY_CELL);

    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_2)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_3)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::PIZZA)));
}

void Boardview::resize(const sf::Vector2f& size) {
    View::resize(size);

    for(Liste<Sommet<Case>>* sommet = _jeu->plateau()->sommets(); sommet; sommet = sommet->next) {
        if(sommet->value->degre() > 0) {
            sf::Sprite sprite(ResourceLoader::getSprite(Sprite::CELL));

            sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
            sprite.setPosition(sommet->value->contenu().position().x * SPRITE_SIZE,
                               sommet->value->contenu().position().y * SPRITE_SIZE);
            _backgroundSprites.push_back(sprite);
        }
    }

    for(Liste<Arete<Chemin, Case>>* arete = _jeu->plateau()->aretes(); arete; arete = arete->next) {

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

        sprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        sprite.setRotation(angle);
        sprite.setPosition((s1_x + vect_x/2) * SPRITE_SIZE, (s1_y + vect_y/2) * SPRITE_SIZE);
       _backgroundSprites.push_back(sprite);
    }
}

void Boardview::render(double timeElapsed) {
    View::render(timeElapsed);

    for(sf::Sprite sprite : _backgroundSprites) {
        window()->draw(sprite);
    }

    _joueur.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _joueur.setPosition(_jeu->joueur()->position().x * SPRITE_SIZE, _jeu->joueur()->position().y * SPRITE_SIZE);
    _joueur.animate(timeElapsed);
    window()->draw(_joueur);

    for(ElementGraphique * p : _jeu->aliments()) {
        sf::Sprite sprite(ResourceLoader::getSprite(p->sprite()));

        sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
        sprite.setPosition(p->position().x * SPRITE_SIZE, p->position().y * SPRITE_SIZE);
        window()->draw(sprite);
    }

    _score = sf::Text("Score:"+std::to_string(_jeu->joueur()->points()), ResourceLoader::getFont(KONGTEXT), 32);
    _score.setPosition(window()->getView().getSize().x - _score.getLocalBounds().width - 20, window()->getView().getSize().y - _score.getLocalBounds().height - 20);
    window()->draw(_score);
}

void Boardview::UpdatePlayer(int x, int y, int angle) {
    Liste<Sommet<Case>>* voisins = _jeu->plateau()->voisins(_jeu->plateau()->sommet(_jeu->joueur()->position()));
    for(Liste<Sommet<Case>>* sommet = voisins; sommet; sommet = sommet->next) {
        try {
            _joueur.setRotation(angle);
            if(sommet->value == _jeu->plateau()->sommet(Position(x,y))) {
                _jeu->joueur()->setPosition(Position(x, y));
                //_jeu->getJoueur()->addPoints(10);

                for(ElementGraphique* p : _jeu->aliments()) {
                    if(p->position().x == x && p->position().y == y) {
                        _jeu->joueur()->addPoints(p->points());
                        _jeu->aliments().erase(std::find(_jeu->aliments().begin(), _jeu->aliments().end(), p));
                    }
                }
            }
        }
        catch(std::exception e) {}
    }

    Liste<Sommet<Case>>::efface1(voisins);
}

void Boardview::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Numpad2:
                UpdatePlayer(_jeu->joueur()->position().x, _jeu->joueur()->position().y+1, 270);
                break;
            case sf::Keyboard::Key::Numpad8:
                UpdatePlayer(_jeu->joueur()->position().x, _jeu->joueur()->position().y-1, 90);
                break;
            case sf::Keyboard::Key::Numpad4:
                UpdatePlayer(_jeu->joueur()->position().x-1, _jeu->joueur()->position().y, 0);
                break;
            case sf::Keyboard::Key::Numpad6:
                UpdatePlayer(_jeu->joueur()->position().x+1, _jeu->joueur()->position().y, 180);
                break;
            case sf::Keyboard::Key::Numpad1:
                UpdatePlayer(_jeu->joueur()->position().x-1, _jeu->joueur()->position().y+1, 315);
                break;
            case sf::Keyboard::Key::Numpad3:
                UpdatePlayer(_jeu->joueur()->position().x+1, _jeu->joueur()->position().y+1, 225);
                break;
            case sf::Keyboard::Key::Numpad7:
                UpdatePlayer(_jeu->joueur()->position().x-1, _jeu->joueur()->position().y-1, 45);
                break;
            case sf::Keyboard::Key::Numpad9:
                UpdatePlayer(_jeu->joueur()->position().x+1, _jeu->joueur()->position().y-1, 135);
                break;
        }
    }
}