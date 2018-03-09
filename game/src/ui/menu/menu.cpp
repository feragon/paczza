#include "menu.h"
#include "ui/views/boardview.h"
#include <ui/resourceloader.h>

Menu::Menu(sf::RenderWindow* window, FenetreJeu *f) :
        View(window, f),
        _selector(ResourceLoader::getSprite(Sprite::RIGHT_CYAN_PINEAPPLE_2)) {

    setFond(EMPTY_CELL);
    _selected = 0;

    setKeyPressedCommand(sf::Keyboard::Up, SharedPtr<MenuMoveSelector>(this, -1));
    setKeyPressedCommand(sf::Keyboard::Down, SharedPtr<MenuMoveSelector>(this, 1));
}

Menu::~Menu() {
    for(MenuItem* item : _items) {
        delete item;
    }
}

void Menu::resize(const sf::Vector2f& size) {
    View::resize(size);

    centerTexts();
}

void Menu::addItem(MenuItem* item) {
    _items.push_back(item);
}

void Menu::render(double timeElapsed) {
    View::render(timeElapsed);

    for(MenuItem* item : _items) {
        window()->draw(*item);
    }

    window()->draw(_selector);
}

void Menu::centerTexts() {
    float halfWidth = window()->getView().getSize().x / 2;
    float halfHeight = window()->getView().getSize().y / 2;
    unsigned int i = 0;

    for(MenuItem* item : _items) {
        item->setPosition(sf::Vector2f(halfWidth - (item->bounds().width / 2), halfHeight + (i * 45)));
        i++;
    }

    updateSelectorPosition();
}

void Menu::updateSelectorPosition() {
    if(_items.size() == 0) {
        return;
    }

    sf::Vector2f position = _items[_selected]->position();

    float top = position.y + (_items[_selected]->bounds().height - _selector.getLocalBounds().height) / 2;
    float left = position.x - _selector.getLocalBounds().width;
    _selector.setPosition(left, top);
}

void Menu::onEvent(const sf::Event& event) {
    try {
        manageEvent(event);
    }
    catch(UnknownCommand& e) {
        _items[_selected]->onEvent(event);
    }
}

void Menu::updateSelector(long offset) {
    offset = offset % (long) _items.size();

    int newSelected = _selected + offset;

    if(newSelected < 0) {
        newSelected += _items.size();
    }
    if(newSelected >= _items.size()) {
        newSelected -= _items.size();
    }

    _selected = (unsigned int)newSelected;
    updateSelectorPosition();
}
