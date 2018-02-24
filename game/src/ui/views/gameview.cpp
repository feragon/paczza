#include <ui/resourceloader.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "gameview.h"

GameView::GameView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game) :
        BoardView(window, f, game->plateau()) {
    _game = game;
    game->addListener(this); //TODO: trouver un meilleur endroit
}

GameView::~GameView() {

}

void GameView::render(double timeElapsed) {
    _game->updateGame(timeElapsed);
    BoardView::render(timeElapsed);

    _score = sf::Text("Score:"+std::to_string(_game->joueur()->points()), ResourceLoader::getFont(KONGTEXT), 32);
    _score.setPosition(window()->getView().getSize().x - _score.getLocalBounds().width - 20, window()->getView().getSize().y - _score.getLocalBounds().height - 20);
    window()->draw(_score);

    generateLifesIndicator(window()->getView().getSize());
}

void GameView::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Numpad2:
                _game->setDirection(DOWN);
                break;
            case sf::Keyboard::Key::Numpad8:
                _game->setDirection(UP);
                break;
            case sf::Keyboard::Key::Numpad4:
                _game->setDirection(LEFT);
                break;
            case sf::Keyboard::Key::Numpad6:
                _game->setDirection(RIGHT);
                break;
            case sf::Keyboard::Key::Numpad1:
                _game->setDirection(LEFT_DOWN);
                break;
            case sf::Keyboard::Key::Numpad3:
                _game->setDirection(RIGHT_DOWN);
                break;
            case sf::Keyboard::Key::Numpad7:
                _game->setDirection(LEFT_UP);
                break;
            case sf::Keyboard::Key::Numpad9:
                _game->setDirection(RIGHT_UP);
                break;
        }
    }
}

void GameView::generateLifesIndicator(const sf::Vector2f& windowSize) {
    const sf::Texture& texture = ResourceLoader::getSprite(OPEN_PIZZA_1);
    double space, x;
    x = space = texture.getSize().x / 2;
    double y = windowSize.y - texture.getSize().y - 10;


    for(int i = 0; i < _game->joueur()->nbLifes(); i++) {
        sf::Sprite s(texture);

        s.setPosition(x, y);
        x += space;

        window()->draw(s);
    }
}

