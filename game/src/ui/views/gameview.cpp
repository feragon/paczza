#include <ui/resourceloader.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <config.h>
#include "gameview.h"
#include "changedirectioncommand.h"

GameView::GameView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game) :
        BoardView(window, f, game->plateau()),
        _playerAnimatedSprite(AnimatedSprite::ANIMATION_CIRCULAR, sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_1)), 16, false) {
    _game = game;
    game->addListener(this);
    updateMonsters();

    _playerAnimatedSprite.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_2)));
    _playerAnimatedSprite.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::OPEN_PIZZA_3)));
    _playerAnimatedSprite.addSprite(sf::Sprite(ResourceLoader::getSprite(Sprite::PIZZA)));
    _playerAnimatedSprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
    _playerAnimatedSprite.setRotation(_game->player().direction() * 45);

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

    drawPlayer(timeElapsed);
    drawMonsters(timeElapsed);

    _score = sf::Text("Score:"+std::to_string(_game->player().points()), ResourceLoader::getFont(KONGTEXT), 32);
    _score.setPosition(window()->getView().getSize().x - _score.getLocalBounds().width - 20, window()->getView().getSize().y - _score.getLocalBounds().height - 20);
    window()->draw(_score);

    generateLifesIndicator(window()->getView().getSize());
}

void GameView::generateLifesIndicator(const sf::Vector2f& windowSize) {
    const sf::Texture& texture = ResourceLoader::getSprite(OPEN_PIZZA_1);
    double space, x;
    x = space = texture.getSize().x / 2;
    double y = windowSize.y - texture.getSize().y - 10;


    for(int i = 0; i < _game->player().nbLifes(); i++) {
        sf::Sprite s(texture);

        s.setPosition(x, y);
        x += space;

        window()->draw(s);
    }
}

void GameView::onNewTurn() {
    updateMonsters();
}

void GameView::onMonsterWeaknessUpdate(const Monster* monster) {
    updateMonsters();
}

void GameView::updateMonsters() {
    _monsters.clear();
    unsigned short monsterNo = 0;

    for(Liste<Monster>* monsters = _game->monsters(); monsters; monsters = monsters->next) {
        unsigned short spriteOffset;
        if(monsters->value->weak()) {
            spriteOffset = LEFT_WEAK_PINEAPPLE - LEFT_GREEN_PINEAPPLE;
        }
        else {
            spriteOffset = monsterNo * 8;
        }
        sf::Sprite s;
        Sprite resource;

        switch(monsters->value->direction()) {
            case LEFT:
                resource = static_cast<Sprite>(LEFT_GREEN_PINEAPPLE + spriteOffset);
                break;
            case LEFT_UP:
                resource = static_cast<Sprite>(LEFT_UP_GREEN_PINEAPPLE + spriteOffset);
                break;

            case UP:
                resource = static_cast<Sprite>(UP_GREEN_PINEAPPLE + spriteOffset);
                break;

            case RIGHT_UP:
                resource = static_cast<Sprite>(RIGHT_UP_GREEN_PINEAPPLE + spriteOffset);
                break;

            case RIGHT:
                resource = static_cast<Sprite>(RIGHT_GREEN_PINEAPPLE + spriteOffset);
                break;

            case RIGHT_DOWN:
                resource = static_cast<Sprite>(RIGHT_DOWN_GREEN_PINEAPPLE + spriteOffset);
                break;

            case DOWN:
                resource = static_cast<Sprite>(DOWN_GREEN_PINEAPPLE + spriteOffset);
                break;

            case LEFT_DOWN:
                resource = static_cast<Sprite>(LEFT_DOWN_GREEN_PINEAPPLE + spriteOffset);
                break;
        }
        s.setTexture(ResourceLoader::getSprite(resource));
        s.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);

        _monsters[monsters->value] = s;
        monsterNo++;
    }
}

void GameView::updateVertice(Sommet<Case>* vertice) {
    genererSpriteElement(vertice->contenu());
}

void GameView::playerMovementBegin(Pacman* player) {
    _playerAnimatedSprite.reset();
}

void GameView::drawPlayer(double timeElapsed) {
    Position<> pos = _game->player().position()->contenu().position();
    double avancement = _game->player().avancement();
    double x = 0;
    double y = 0;
    Direction d = _game->player().direction();
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

    _playerAnimatedSprite.setRotation(_game->player().direction() * 45);
    _playerAnimatedSprite.setPosition((pos.x + avancement * x) * SPRITE_SIZE, (pos.y + avancement * y) * SPRITE_SIZE);
    _playerAnimatedSprite.animate(timeElapsed);
    window()->draw(_playerAnimatedSprite);
}

void GameView::drawMonsters(double timeElapsed) {
    for(std::pair<const Monster* const, sf::Sprite>& pair : _monsters) {
        Position<> monsterPos = pair.first->position()->contenu().position();
        double avancement = pair.first->avancement();
        double x = 0;
        double y = 0;
        Direction d = pair.first->direction();
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

        pair.second.setPosition((monsterPos.x + avancement * x) * SPRITE_SIZE, (monsterPos.y + avancement * y) * SPRITE_SIZE);
        window()->draw(pair.second);
    }
}

void GameView::updateEdge(Arete<Chemin, Case>* edge) {
    Position<> p1 = edge->debut()->contenu().position();
    Position<> p2 = edge->fin()->contenu().position();

    if(p1 == p2) {
        return;
    }

    Position<double> moveVect = p1 - p2;

    sf::Sprite sprite(ResourceLoader::getSprite(Sprite::COCAINE));

    sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    sprite.setPosition((p2.x + moveVect.x / 2) * SPRITE_SIZE,
                       (p2.y + moveVect.y / 2) * SPRITE_SIZE);

    _aretesMarquees[edge] = sprite;
}
