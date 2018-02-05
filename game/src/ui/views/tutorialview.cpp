#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include "tutorialview.h"

TutorialView::TutorialView(sf::RenderWindow* window, FenetreJeu* f) :
        View(window, f),
        _boardView(window, f, new Jeu()) {
    _boardView.setDemonstrationMode(true);
    _sendEvents = false;
    _showText = true;

    _state = WELCOME;
    _indication = sf::Text("Hello", ResourceLoader::getFont(KONGTEXT), 64);
    _returnKey = sf::Sprite(ResourceLoader::getSprite(RETURN_KEY));
    center(_indication, _returnKey);
}

void TutorialView::onEvent(const sf::Event& event) {
    if(_sendEvents) {
        _boardView.onEvent(event);
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
    _boardView.render(timeElapsed);

    if(_showText) {
        window()->draw(_indication);
        window()->draw(_returnKey);
    }
}

void TutorialView::resize(const sf::Vector2f& size) {
    _boardView.resize(size);
}

void TutorialView::center(sf::Text& text, sf::Sprite& sprite) {
    sf::FloatRect spriteSize = sprite.getLocalBounds();
    sf::FloatRect textSize = text.getLocalBounds();

    float width = spriteSize.width + textSize.width;
    text.setPosition(
            (window()->getView().getSize().x - width) / 2,
            (window()->getView().getSize().y - textSize.height) / 2
    );

    sprite.setPosition(
            (window()->getView().getSize().x - width) / 2 + textSize.width,
            (window()->getView().getSize().y - textSize.height) / 2
    );
}

void TutorialView::update() {
    _state = static_cast<State>(_state + 1);
    switch (_state) {
        case PACZZA_PRESENTATION:
            _indication.setString(L"Voici Paczza,\nvotre pizza préférée.");
            _indication.setCharacterSize(32);
            break;

        case END:
            fenetreJeu()->vuePrecedente();
            break;

        default:
            break;
    }

    center(_indication, _returnKey);
}
