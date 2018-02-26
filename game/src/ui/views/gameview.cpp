#include <ui/resourceloader.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "gameview.h"
#include "changedirectioncommand.h"

GameView::GameView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game) :
        BoardView(window, f, game->plateau()) {
    _game = game;
    game->addListener(this); //TODO: trouver un meilleur endroit
    
    setKeyPressedCommand(sf::Keyboard::Numpad1, SharedPtr<ChangeDirectionCommand>(game.get(), LEFT_DOWN));
    setKeyPressedCommand(sf::Keyboard::Numpad2, SharedPtr<ChangeDirectionCommand>(game.get(), DOWN));
    setKeyPressedCommand(sf::Keyboard::Numpad3, SharedPtr<ChangeDirectionCommand>(game.get(), RIGHT_DOWN));
    setKeyPressedCommand(sf::Keyboard::Numpad4, SharedPtr<ChangeDirectionCommand>(game.get(), LEFT));
    setKeyPressedCommand(sf::Keyboard::Numpad6, SharedPtr<ChangeDirectionCommand>(game.get(), RIGHT));
    setKeyPressedCommand(sf::Keyboard::Numpad7, SharedPtr<ChangeDirectionCommand>(game.get(), LEFT_UP));
    setKeyPressedCommand(sf::Keyboard::Numpad8, SharedPtr<ChangeDirectionCommand>(game.get(), UP));
    setKeyPressedCommand(sf::Keyboard::Numpad9, SharedPtr<ChangeDirectionCommand>(game.get(), RIGHT_UP));
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

