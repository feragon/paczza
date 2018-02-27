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
    double frame = 0;
    bool forward = true;

    for(auto pair : _monsters) {
        if(pair.first->weak()) {
            frame = pair.second.frame();
            forward = pair.second.forward();
            break;
        }
    }

    _monsters.clear();
    unsigned short monsterNo = 0;

    for(Liste<Monster>* monsters = _game->monsters(); monsters; monsters = monsters->next) {
        unsigned short spriteOffset;
        unsigned short nbFrames;
        if(monsters->value->weak()) {
            if(monsters->value->returnHome()) {
                spriteOffset = LEFT_EYES_PINEAPPLE - LEFT_GREEN_PINEAPPLE;
                nbFrames = EYES_MONSTER_FRAMES;
            }
            else {
                spriteOffset = LEFT_WEAK_PINEAPPLE_1 - LEFT_GREEN_PINEAPPLE;
                nbFrames = WEAK_MONSTER_FRAMES;
            }
        }
        else {
            spriteOffset = monsterNo * NB_DIRECTIONS * MONSTER_FRAMES;
            nbFrames = MONSTER_FRAMES;
        }

        Sprite resource = static_cast<Sprite>(LEFT_GREEN_PINEAPPLE + monsters->value->direction() + spriteOffset);
        sf::Sprite s(ResourceLoader::getSprite(resource));
        AnimatedSprite as(AnimatedSprite::ANIMATION_CIRCULAR, s, 2, true);

        for(unsigned short i = 1; i < nbFrames; i++) {
            s.setTexture(ResourceLoader::getSprite(static_cast<Sprite>(resource + i * NB_DIRECTIONS)));
            as.addSprite(s);
        }

        as.setForward(forward);
        try {
            as.setFrame(frame);
        }
        catch (std::runtime_error& e) {

        }

        as.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);

        _monsters.insert(std::pair<Monster*, AnimatedSprite>(monsters->value, as));
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
    for(std::pair<const Monster* const, AnimatedSprite>& pair : _monsters) {
        if(pair.first->weakTime() > 0) {
            pair.second.setFps((WEAK_TIME - pair.first->weakTime()) * 2);
        }
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
        pair.second.animate(timeElapsed);
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
