#include <ui/resourceloader.h>
#include <SFML/Window/Event.hpp>
#include <game/nomorelevels.h>
#include <game/noremaininglife.h>
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

    if(_game->stopped()) {
        const char* title;
        if(_game->remainingPoints() == 0) {
            title = "YOU WON!";
        }
        else {
            if(_game->joueur()->nbLifes() > 0) {
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

void PacmanGameView::onEvent(const sf::Event& event) {
    GameView::onEvent(event);

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        try {
            _game->start();
            genererSpritesElements();
            updateLevelText();
        }
        catch(NoMoreLevels& e) {
            fenetreJeu()->vuePrecedente();
        }
        catch(NoRemainingLife& e) {
            fenetreJeu()->vuePrecedente();
        }
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
