#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <config.h>
#include "tutorialview.h"
#include "updatetutorialcommand.h"

TutorialView::TutorialView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game) :
        View(window, f),
        _gameView(window, f, game) {
    _sendEvents = false;
    _showText = true;

    _state = WELCOME;
    _indication = sf::Text("Hello", ResourceLoader::getFont(KONGTEXT), 64);
    _indication.setOutlineColor(sf::Color::Black);
    _indication.setOutlineThickness(2);
    _returnKey = sf::Sprite(ResourceLoader::getSprite(RETURN_KEY));
    _fog = nullptr;
    center(_indication, _returnKey);



    for (std::pair<const Monster* const, AnimatedSprite>& pair : _gameView.monsterAnimatedSprites()) {
        pair.second.setInfinite(false);
    }

    _commandReceiver.setKeyPressedCommand(sf::Keyboard::Return, SharedPtr<UpdateTutorialCommand>(this));
}

TutorialView::~TutorialView() {
    if(_fog) {
        delete _fog;
    }
}

void TutorialView::onEvent(const sf::Event& event) {
    try {
        _commandReceiver.manageEvent(event);
    }
    catch (UnknownCommand& e) {
        if(_sendEvents) {
            _gameView.onEvent(event);
        }
    }
}

void TutorialView::render(double timeElapsed) {
    View::render(timeElapsed);
    _gameView.render(timeElapsed);

    if(_fog) {
        window()->draw(*_fog);
    }

    if(_showText) {
        window()->draw(_indication);
        window()->draw(_returnKey);
    }
}

void TutorialView::resize(const sf::Vector2f& size) {
    _gameView.resize(size);
}

void TutorialView::center(sf::Text& text, sf::Sprite& sprite) {
    sf::FloatRect spriteSize = sprite.getLocalBounds();
    sf::FloatRect textSize = text.getLocalBounds();

    float width = spriteSize.width + textSize.width;
    text.setPosition(
            (window()->getView().getSize().x - width) / 2,
            5
    );

    sprite.setPosition(
            (window()->getView().getSize().x - width) / 2 + textSize.width,
            5
    );
}

void TutorialView::update() {
    if(_fog) {
        delete _fog;
        _fog = nullptr;
    }

    _state = static_cast<State>(_state + 1);
    switch (_state) {
        case PACZZA_PRESENTATION: {
            Position<> pos = (_gameView.game()->player().position()->contenu().position()) * SPRITE_SIZE;
            _fog = new Fog(window()->getView().getSize(), sf::Vector2f(pos.x, pos.y));

            _indication.setString(L"Voici Paczza,\nvotre pizza préférée.");
            _indication.setCharacterSize(21);
            _gameView.playerAnimatedSprite().setInfinite(true);
            break;
        }

        case OBJECTIVE: {
            _gameView.playerAnimatedSprite().setInfinite(false);

            _indication.setString("Vous devez nettoyer toutes\nles traces de sauce tomate.");
            break;
        }

        case MONSTERS: {
            _indication.setString(L"En évitant les monstres.");

            Position<float>* pos = nullptr;
            size_t i = 0;
            for (std::pair<const Monster* const, AnimatedSprite>& pair : _gameView.monsterAnimatedSprites()) {
                if(!pos) {
                    pos = new Position<float>(pair.first->position()->contenu().position());
                }
                else {
                    *pos = ((*pos) + pair.first->position()->contenu().position());
                }

                pair.second.setInfinite(true);
                i++;
            }

            if(pos) {
                *pos = (*pos) * (SPRITE_SIZE/i);
                _fog = new Fog(window()->getView().getSize(), sf::Vector2f(pos->x, pos->y));
            }

            delete pos;
            break;
        }

        case SUPER_POINTS: {
            _superPointFound = false;
            _indication.setString(L"Les super points vous\nrapporteront plus de points.");

            Liste<Sommet<Case<Element>>>* sommet = _gameView.game()->plateau()->sommets();
            for(; sommet; sommet = sommet->next) {
                if(!sommet->value->contenu().element()) {
                    continue;
                }
                sommet->value->contenu().element()->accept(*this);
                if(_superPointFound) {
                    Position<> pos = sommet->value->contenu().position() * SPRITE_SIZE;
                    _fog = new Fog(window()->getView().getSize(), sf::Vector2f(pos.x, pos.y));
                    break;
                }
            }

            break;
        }

        case WEAK_MONSTERS: {
            _indication.setString(L"Et rendent les\nmonstres vulnérables.");

            for(Liste<Monster>* monster = _gameView.game()->monsters(); monster; monster = monster->next) {
                monster->value->setWeak(true);
                _gameView.onMonsterWeaknessUpdate(monster->value);
            }

            for (std::pair<const Monster* const, AnimatedSprite>& pair : _gameView.monsterAnimatedSprites()) {
                pair.second.setInfinite(true);
            }
            break;
        }

        case LIFES:
            _indication.setString(L"Vous commencez avec\ntrois vies.");
            for(Liste<Monster>* monster = _gameView.game()->monsters(); monster; monster = monster->next) {
                monster->value->setWeak(false);
                _gameView.onMonsterWeaknessUpdate(monster->value);
            }
            break;

        case SCORE:
            _indication.setString(L"L'objectif est de faire\nle plus grand score.");
            break;

        case END:
            fenetreJeu()->vuePrecedente();
            return;

        default:
            break;
    }

    center(_indication, _returnKey);
}

void TutorialView::visite(const Point& point) {

}

void TutorialView::visite(const SuperPoint& superPoint) {
    _superPointFound = true;
}

void TutorialView::visite(const Teleporter& teleporter) {

}
