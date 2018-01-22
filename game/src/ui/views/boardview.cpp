#include <config.h>
#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
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

    for(Liste<Monster>* monstres = _jeu->monstres(); monstres; monstres = monstres->next) {
        sf::Sprite s(ResourceLoader::getSprite(RIGHT_PINEAPPLE));
        s.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
        s.setPosition(monstres->value->position().x * SPRITE_SIZE, monstres->value->position().y * SPRITE_SIZE);
        window()->draw(s);
    }

    _score = sf::Text("Score:"+std::to_string(_jeu->joueur()->points()), ResourceLoader::getFont(KONGTEXT), 32);
    _score.setPosition(window()->getView().getSize().x - _score.getLocalBounds().width - 20, window()->getView().getSize().y - _score.getLocalBounds().height - 20);
    window()->draw(_score);
}

void BoardView::updatePlayer(int x, int y, int angle) {
    _joueur.reset();

    Position<> p(x, y);

    Sommet<Case>* sommetActuel = _jeu->plateau()->sommet(_jeu->joueur()->position());
    Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>* voisins = _jeu->plateau()->adjacences(sommetActuel);

    for(Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>* sommet = voisins; sommet; sommet = sommet->next) {
        try {
            _joueur.setRotation(angle);
            if(sommet->value->first->contenu().position() == p) {

                Arete<Chemin, Case>* arete = sommet->value->second;
                arete->contenu().setChaleur(UINT8_MAX);

                Position<> s1 = _jeu->joueur()->position();
                Position<> s2 = p;
                float vect_x = s2.x - s1.x;
                float vect_y = s2.y - s1.y;

                _jeu->joueur()->resetDeplacement();
                for(double k = 1; k >= 0; k-= 0.07) {
                    _jeu->joueur()->ajouterDeplacement(_jeu->joueur()->position().x + k*vect_x, _jeu->joueur()->position().y + k*vect_y);
                }

                _jeu->joueur()->setPosition(p);
                sommet->value->first->contenu().heberge(*(_jeu->joueur()));
                genererSpriteElement(sommet->value->first->contenu());

                sf::Sprite sprite(ResourceLoader::getSprite(Sprite::COCAINE));
                sprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
                sprite.setPosition((s1.x + vect_x/2) * SPRITE_SIZE, (s1.y + vect_y/2) * SPRITE_SIZE);
                _aretesMarquees[arete] = sprite;

                break;
            }
        }
        catch(std::exception e) {}
    }

    Liste<std::pair<Sommet<Case>*, Arete<Chemin, Case>*>>::efface2(voisins);
}

void BoardView::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Numpad2:
                updatePlayer(_jeu->joueur()->position().x, _jeu->joueur()->position().y + 1, 270);
                break;
            case sf::Keyboard::Key::Numpad8:
                updatePlayer(_jeu->joueur()->position().x, _jeu->joueur()->position().y - 1, 90);
                break;
            case sf::Keyboard::Key::Numpad4:
                updatePlayer(_jeu->joueur()->position().x - 1, _jeu->joueur()->position().y, 0);
                break;
            case sf::Keyboard::Key::Numpad6:
                updatePlayer(_jeu->joueur()->position().x + 1, _jeu->joueur()->position().y, 180);
                break;
            case sf::Keyboard::Key::Numpad1:
                updatePlayer(_jeu->joueur()->position().x - 1, _jeu->joueur()->position().y + 1, 315);
                break;
            case sf::Keyboard::Key::Numpad3:
                updatePlayer(_jeu->joueur()->position().x + 1, _jeu->joueur()->position().y + 1, 225);
                break;
            case sf::Keyboard::Key::Numpad7:
                updatePlayer(_jeu->joueur()->position().x - 1, _jeu->joueur()->position().y - 1, 45);
                break;
            case sf::Keyboard::Key::Numpad9:
                updatePlayer(_jeu->joueur()->position().x + 1, _jeu->joueur()->position().y - 1, 135);
                break;
        }
    }
}
