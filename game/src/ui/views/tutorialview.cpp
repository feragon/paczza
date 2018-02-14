#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <config.h>
#include "tutorialview.h"

TutorialView::TutorialView(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f),
        _gameView(window, f, SharedPtr<Jeu>()) {
    _sendEvents = false;
    _showText = true;

    _state = WELCOME;
    _indication = sf::Text("Hello", ResourceLoader::getFont(KONGTEXT), 64);
    _indication.setOutlineColor(sf::Color::Black);
    _indication.setOutlineThickness(2);
    _returnKey = sf::Sprite(ResourceLoader::getSprite(RETURN_KEY));
    _fog = nullptr;
    center(_indication, _returnKey);
}

TutorialView::~TutorialView() {
    if(_fog) {
        delete _fog;
    }
}

void TutorialView::onEvent(const sf::Event& event) {
    if(_sendEvents) {
        _gameView.onEvent(event);
    }
    else {
        if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::Key::Return:
                    update();
            }
        }

        center(_indication, _returnKey);
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
            Position<> pos = (_gameView.game()->joueur()->position()->contenu().position() - 1) * SPRITE_SIZE;
            _fog = new Fog(window()->getView().getSize(), sf::Vector2f(pos.x, pos.y));

            _indication.setString(L"Voici Paczza,\nvotre pizza préférée.");
            _indication.setCharacterSize(32);
            break;
        }

        case END:
            fenetreJeu()->vuePrecedente();
            break;

        default:
            break;
    }

    center(_indication, _returnKey);
}
