#include <ui/resourceloader.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <config.h>
#include "gameview.h"
#include "changedirectioncommand.h"
#include <game/teleporter.h>
#include <game/point.h>
#include <game/superpoint.h>
#include <game/noremaininglife.h>
#include <ui/transform.h>

GameView::GameView(sf::RenderWindow* window, FenetreJeu* f, SharedPtr<Jeu> game) :
        BoardView(window, f, game->plateau()),
        _playerAnimatedSprite(AnimatedSprite::ANIMATION_CIRCULAR, sf::Sprite(ResourceLoader::getSprite(Sprite::LEFT_PIZZA_1)), 16, false),
        _game(game) {
    game->addListener(this);
    updateMonsters();
    updatePlayer();

    _superPointId = 0;
    genererSpritesElements();

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

    for(const std::pair<const Position<>, sf::Sprite>& p : _elements) {
        window()->draw(p.second);
    }

    for(std::pair<const Position<>, AnimatedSprite>& p : _animatedElements) {
        p.second.animate(timeElapsed);
        window()->draw(p.second);
    }

    double chaleurEnlevee = (UINT8_MAX / COOLDOWN_TIME) * timeElapsed;
    auto it = _aretesMarquees.begin();
    while (it != _aretesMarquees.end()) {
        Arete<Chemin, Case<Element>>* arete = it->first;
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

    for(const sf::Sprite& s : _lifes) {
        window()->draw(s);
    }
}

void GameView::generateLifesIndicator(const sf::Vector2f& windowSize) {
    _lifes.clear();
    const sf::Texture& texture = ResourceLoader::getSprite(LEFT_PIZZA_1);
    double space, x;
    x = space = texture.getSize().x / 2;
    double y = windowSize.y - texture.getSize().y - 10;


    for(int i = 0; i < _game->player().nbLifes(); i++) {
        sf::Sprite s(texture);

        s.setPosition(x, y);
        x += space;

        _lifes.push_back(s);
    }
}

void GameView::onNewTurn() {
    updateMonsters();
    _sound.stop();

    try {
        _sound.setBuffer(ResourceLoader::getSound(_sounds.at(_game->player().position()->contenu().position())));
        _sound.play();
    }
    catch (std::out_of_range& e) {

    }
}

void GameView::onMonsterWeaknessUpdate(const Monster* monster) {
    updateMonsters();
}

void GameView::updateMonsters() {
    double frame = 0;
    bool forward = true;

    for(auto pair : _monsters) {
        frame = pair.second.frame();
        forward = pair.second.forward();
        break;
    }

    _monsters.clear();
    unsigned short monsterNo = 0;

    for(Liste<Monster>* monsters = _game->monsters(); monsters; monsters = monsters->next) {
        unsigned short spriteOffset;
        unsigned short nbFrames;
        if(monsters->value->weak()) {
            if(monsters->value->returnHome()) {
                spriteOffset = LEFT_EYES_PINEAPPLE - LEFT_RED_PINEAPPLE_1;
                nbFrames = EYES_MONSTER_FRAMES;
            }
            else {
                spriteOffset = LEFT_WEAK_PINEAPPLE_1 - LEFT_RED_PINEAPPLE_1;
                nbFrames = WEAK_MONSTER_FRAMES;
            }
        }
        else {
            spriteOffset = monsterNo * NB_DIRECTIONS * MONSTER_FRAMES;
            nbFrames = MONSTER_FRAMES;
        }

        Sprite resource = static_cast<Sprite>(LEFT_RED_PINEAPPLE_1 + monsters->value->direction() + spriteOffset);
        sf::Sprite s(ResourceLoader::getSprite(resource));
        AnimatedSprite as(AnimatedSprite::ANIMATION_CIRCULAR, s, 4, true);

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

void GameView::updateVertice(Sommet<Case<Element>>* vertice) {
    genererSpriteElement(vertice->contenu());
}

void GameView::playerMovementBegin(Pacman* player) {
    _playerAnimatedSprite.reset();
    updatePlayer(); //TODO: seulement en cas de changement de direction
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

    _playerAnimatedSprite.setPosition(transform(sf::Vector2f(pos.x + avancement * x, pos.y + avancement * y)));
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

        pair.second.setPosition(transform(sf::Vector2f(monsterPos.x + avancement * x, monsterPos.y + avancement * y)));
        pair.second.animate(timeElapsed);
        window()->draw(pair.second);
    }
}

void GameView::updateEdge(Arete<Chemin, Case<Element>>* edge) {
    Position<double> p1 = edge->debut()->contenu().position();
    Position<double> p2 = edge->fin()->contenu().position();

    if(p1 == p2) {
        return;
    }

    Position<double> moveVect = (p1 - p2) * 0.5;

    sf::Sprite sprite(ResourceLoader::getSprite(Sprite::COCAINE));

    sprite.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    sprite.setPosition(transform<float>(p2 + moveVect));

    _aretesMarquees[edge] = sprite;
}

void GameView::updatePlayer() {
    Sprite resource = static_cast<Sprite>(LEFT_PIZZA_1 + _game->player().direction());
    sf::Sprite sprite = sf::Sprite(ResourceLoader::getSprite(resource));

    _playerAnimatedSprite = AnimatedSprite(AnimatedSprite::ANIMATION_CIRCULAR, sprite, PLAYER_FRAMES/MOVEMENT_TIME, false);
    _playerAnimatedSprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);

    for(int i = 1; i < PLAYER_FRAMES; i++) {
        resource = static_cast<Sprite>(resource + NB_DIRECTIONS);
        sprite = sf::Sprite(ResourceLoader::getSprite(resource));
        _playerAnimatedSprite.addSprite(sprite);
    }
}

void GameView::genererSpritesElements() {
    _elements.clear();
    _animatedElements.clear();
    _sounds.clear();

    for(Liste<Sommet<Case<Element>>>* l = _game->plateau()->sommets(); l; l = l->next) {
        genererSpriteElement(l->value->contenu());
    }
}

void GameView::genererSpriteElement(const Case<Element>& c) {
    _elements.erase(c.position());
    _animatedElements.erase(c.position());
    _sounds.erase(c.position());

    if(c.element()) {
        c.element()->accept(*this);
    }
}


void GameView::visite(const Point& point) {
    if(!point.position()) {
        return;
    }

    placeElement(point, sf::Sprite(ResourceLoader::getSprite(TOMATO_SMUDGE)));
    placeSound(point, EAT);
}

void GameView::visite(const SuperPoint& superPoint) {
    if(!superPoint.position()) {
        return;
    }

    Sprite resource;
    _superPointId++;

    switch (_superPointId) {
        case 1:
            resource = CHEESE;
            break;

        case 2:
            resource = TOMATO;
            break;

        case 3:
            resource = HAM;
            break;

        case 4:
            resource = MUSHROOM;
            _superPointId = 0;
            break;

        default:
            resource = CHEESE;
            _superPointId = 0;
    }

    placeElement(superPoint, sf::Sprite(ResourceLoader::getSprite(resource)));
    placeSound(superPoint, BONUS);
}

void GameView::visite(const Teleporter& teleporter) {
    if(!teleporter.position()) {
        return;
    }

    AnimatedSprite as(AnimatedSprite::ANIMATION_LINERAR, sf::Sprite(ResourceLoader::getSprite(TELEPORTER_1)), 4, true);
    as.addSprite(sf::Sprite(ResourceLoader::getSprite(TELEPORTER_2)));
    as.addSprite(sf::Sprite(ResourceLoader::getSprite(TELEPORTER_3)));

    placeElement(teleporter, as);
    placeSound(teleporter, TELEPORT);
}

void GameView::placeElement(const Element& element, sf::Sprite sprite) {
    moveElement(element, sprite);
    _elements[element.position()->position()] = sprite;
}

void GameView::placeElement(const Element& element, AnimatedSprite sprite) {
    moveElement(element, sprite);
    _animatedElements.insert(std::pair<Position<>, AnimatedSprite>(element.position()->position(), sprite));
}

void GameView::moveElement(const Element& element, sf::Transformable& transformable) const {
    transformable.setOrigin(SPRITE_SIZE / 2, SPRITE_SIZE / 2);
    transformable.setPosition(transform<float>(element.position()->position()));
}

void GameView::placeSound(const Element& element, Sound sound) {
    _sounds.insert(std::pair<Position<>, Sound>(element.position()->position(), sound));
}

void GameView::resize(const sf::Vector2f& size) {
    BoardView::resize(size);

    generateLifesIndicator(window()->getView().getSize());
}

void GameView::startGame() {
    try {
        _game->start();
        generateLifesIndicator(window()->getView().getSize());
        genererSpritesElements();
        updatePlayer();
        updateMonsters();
    }
    catch(NoRemainingLife& e) {
        fenetreJeu()->vuePrecedente();
    }
}
