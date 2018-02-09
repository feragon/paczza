#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <game/onplayerpositionchanged.h>
#include <cmath>
#include "boardview.h"
#include <SFML/Audio.hpp>

BoardView::BoardView(sf::RenderWindow* window, FenetreJeu* f, Jeu* jeu) :
        View(window, f),
        _joueur(AnimatedSprite::ANIMATION_CIRCULAR, sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_1)), 16, false) {


    _jeu = jeu;
    setFond(Sprite::EMPTY_CELL);

    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_2)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_3)));
    _joueur.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::PIZZA)));
    _joueur.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _joueur.setRotation(_jeu->joueur()->direction() * 45);

    _jeu->setOnPlayerPositionChanged(this);

    _demonstrationMode = false;
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

    for(const sf::Sprite& sprite : _backgroundSprites) {
        window()->draw(sprite);
    }

    Position<> pos = _jeu->joueur()->position()->contenu().position();
    double avancement = _jeu->joueur()->avancement();
    double x = 0;
    double y = 0;
    Direction d = _jeu->joueur()->direction();
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

    _joueur.setPosition((pos.x + avancement * x) * SPRITE_SIZE, (pos.y + avancement * y) * SPRITE_SIZE);
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

    for(Liste<Monster>* monstres = _jeu->monstres(); monstres; monstres = monstres->next) {
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

    _score = sf::Text("Score:"+std::to_string(_jeu->joueur()->points()), ResourceLoader::getFont(KONGTEXT), 32);
    _score.setPosition(window()->getView().getSize().x - _score.getLocalBounds().width - 20, window()->getView().getSize().y - _score.getLocalBounds().height - 20);
    window()->draw(_score);

    generateLifesIndicator(window()->getView().getSize());
    _elements[Position<>(6,1)].rotate(1);
    _elements[Position<>(6,8)].rotate(1);

    if(_jeu->stopped() && !_demonstrationMode) {
        const char* title;
        if(_jeu->remainingPoints() == 0) {
            title = "YOU WON!";
        }
        else {
            if(_jeu->joueur()->nbLifes() > 0) {
                title = "READY?!";
            }
            else {
                title = "GAME OVER!";
            }
        }
        sf::Text gameover = sf::Text(title, ResourceLoader::getFont(KONGTEXT), 72);
        gameover.setOrigin(gameover.getLocalBounds().width / 2, gameover.getLocalBounds().height / 2);
        gameover.setPosition(window()->getView().getSize().x / 2, window()->getView().getSize().y / 2);
        window()->draw(gameover);

        sf::Sprite returnKey(ResourceLoader::getSprite(RETURN_KEY));
        returnKey.setOrigin(0, returnKey.getLocalBounds().height / 3);
        returnKey.setPosition(gameover.getGlobalBounds().left + gameover.getGlobalBounds().width, window()->getView().getSize().y / 2);
        window()->draw(returnKey);
    }
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
            case sf::Keyboard::Key::Return:
                if(_jeu->joueur()->nbLifes() == 0)
                    fenetreJeu()->vuePrecedente();
                else
                    _jeu->start();
                break;
        }
    }
}

void BoardView::onPlayerPositionChanged(const Position<>& oldPosition, const Position<>& newPosition) {
    Sommet<Case>* oldVertice = _jeu->plateau()->sommet(oldPosition);
    Sommet<Case>* newVertice = _jeu->plateau()->sommet(newPosition);

    _joueur.setRotation(_jeu->joueur()->direction() * 45);
    genererSpriteElement(newVertice->contenu());

    if(oldPosition != newPosition) {
        _joueur.reset();
        Arete<Chemin, Case>* arete = _jeu->plateau()->getAreteParSommets(oldVertice, newVertice);

        if(!arete) {
            return; //TODO
        }

        Position<double> moveVect = newPosition - oldPosition;

        sf::Sprite sprite(ResourceLoader::getSprite(Sprite::COCAINE));

        sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
        sprite.setPosition((oldPosition.x + moveVect.x / 2) * SPRITE_SIZE,
                           (oldPosition.y + moveVect.y / 2) * SPRITE_SIZE);


        _aretesMarquees[arete] = sprite;
    }
}

void BoardView::generateLifesIndicator(const sf::Vector2f& windowSize) {
    const sf::Texture& texture = ResourceLoader::getSprite(OPEN_PIZZA_1);
    double space, x;
    x = space = texture.getSize().x / 2;
    double y = windowSize.y - texture.getSize().y - 10;


    for(int i = 0; i < _jeu->joueur()->nbLifes(); i++) {
        sf::Sprite s(texture);

        s.setPosition(x, y);
        x += space;

        window()->draw(s);
    }
}