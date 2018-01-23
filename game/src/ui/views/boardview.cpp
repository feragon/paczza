#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <game/onplayerpositionchanged.h>
#include "boardview.h"

BoardView::BoardView(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f),
        _joueur(AnimatedSprite::ANIMATION_CIRCULAR, sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_1)), 16, false) {


    _jeu = new Jeu();
    setFond(Sprite::EMPTY_CELL);

    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_2)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_3)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::PIZZA)));
    _joueur.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _joueur.setRotation(_jeu->direction() * 45);

    _jeu->setOnPlayerPositionChanged(this);
}

BoardView::~BoardView() {
    delete _jeu;
}

void BoardView::genererSpritesElements() {
    for(Liste<Sommet<Case>>* l = _jeu->plateau()->sommets(); l; l = l->next) {
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

    _jeu->updateGame(timeElapsed);

    for(sf::Sprite sprite : _backgroundSprites) {
        window()->draw(sprite);
    }

    Position<double>* pos = _jeu->joueur()->prochainDeplacement();

    _joueur.setPosition(pos->x * SPRITE_SIZE, pos->y * SPRITE_SIZE);
    _joueur.animate(timeElapsed);
    window()->draw(_joueur);

    for(std::pair<const Position<>, sf::Sprite> p : _elements) {
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

    sf::Rect<float> p(_joueur.getGlobalBounds().left + SPRITE_SIZE/4, _joueur.getGlobalBounds().top + SPRITE_SIZE/4, SPRITE_SIZE/2, SPRITE_SIZE/2);

    for(Liste<Monster>* monstres = _jeu->monstres(); monstres; monstres = monstres->next) {
        sf::Sprite s(ResourceLoader::getSprite(RIGHT_PINEAPPLE));
        s.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        s.setPosition(monstres->value->position().x * SPRITE_SIZE, monstres->value->position().y * SPRITE_SIZE);
        window()->draw(s);

        //Detecteur de collisions
        sf::Rect<float> m(s.getGlobalBounds().left + SPRITE_SIZE/4, s.getGlobalBounds().top + SPRITE_SIZE/4, SPRITE_SIZE/2, SPRITE_SIZE/2);

        if(p.intersects(m)) {
            sf::Text gameover = sf::Text("GAME OVER", ResourceLoader::getFont(KONGTEXT), 72);
            gameover.setOrigin(gameover.getLocalBounds().width / 2, gameover.getLocalBounds().height / 2);
            gameover.setPosition(window()->getView().getSize().x /2, window()->getView().getSize().y /2);
            window()->draw(gameover);
        }
    }

    _score = sf::Text("Score:"+std::to_string(_jeu->joueur()->points()), ResourceLoader::getFont(KONGTEXT), 32);
    _score.setPosition(window()->getView().getSize().x - _score.getLocalBounds().width - 20, window()->getView().getSize().y - _score.getLocalBounds().height - 20);
    window()->draw(_score);
}

void BoardView::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Numpad2:
                _jeu->setDirection(DOWN);
                break;
            case sf::Keyboard::Key::Numpad8:
                _jeu->setDirection(UP);
                break;
            case sf::Keyboard::Key::Numpad4:
                _jeu->setDirection(LEFT);
                break;
            case sf::Keyboard::Key::Numpad6:
                _jeu->setDirection(RIGHT);
                break;
            case sf::Keyboard::Key::Numpad1:
                _jeu->setDirection(LEFT_DOWN);
                break;
            case sf::Keyboard::Key::Numpad3:
                _jeu->setDirection(RIGHT_DOWN);
                break;
            case sf::Keyboard::Key::Numpad7:
                _jeu->setDirection(LEFT_UP);
                break;
            case sf::Keyboard::Key::Numpad9:
                _jeu->setDirection(RIGHT_UP);
                break;
        }
    }
}

void BoardView::onPlayerPositionChanged(const Position<>& oldPosition, const Position<>& newPosition) {
    Sommet<Case>* oldVertice = _jeu->plateau()->sommet(oldPosition);
    Sommet<Case>* newVertice = _jeu->plateau()->sommet(newPosition);

    _joueur.setRotation(_jeu->direction() * 45);
    genererSpriteElement(newVertice->contenu());

    if(oldPosition != newPosition) {
        _joueur.reset();
        Position<double> moveVect = newPosition - oldPosition;

        sf::Sprite sprite(ResourceLoader::getSprite(Sprite::COCAINE));

        sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
        sprite.setPosition((oldPosition.x + moveVect.x / 2) * SPRITE_SIZE,
                           (oldPosition.y + moveVect.y / 2) * SPRITE_SIZE);
        _aretesMarquees[_jeu->plateau()->getAreteParSommets(oldVertice, newVertice)] = sprite;
    }
}
