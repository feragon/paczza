#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include "pacmangameview.h"

PacmanGameView::PacmanGameView(sf::RenderWindow* window, FenetreJeu* f, const SharedPtr<PacmanGame>& game) :
    GameView(window, f, game),
    _level("", ResourceLoader::getFont(KONGTEXT)),
    _game(game) {

    updateLevelText();
}

void PacmanGameView::render(double timeElapsed) {
    GameView::render(timeElapsed);

    window()->draw(_level);
}

void PacmanGameView::onEvent(const sf::Event& event) {
    GameView::onEvent(event);

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        updateLevelText();
    }
}

void PacmanGameView::updateLevelText() {
    _level.setString("Level:" + std::to_string(_game->level()));
}

void PacmanGameView::resize(const sf::Vector2f& size) {
    BoardView::resize(size);

    updateLevelPosition();
}

void PacmanGameView::updateLevelPosition() {
    sf::Vector2u size = window()->getSize();
    _level.setPosition((size.x - _level.getLocalBounds().width) / 2, size.y - _level.getLocalBounds().height - 20);
}
