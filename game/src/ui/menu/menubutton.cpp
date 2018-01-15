#include "menubutton.h"
#include <SFML/Graphics/RenderTarget.hpp>

MenuButton::MenuButton(const std::wstring& title, const std::function<void(void)>& callback) {
    if (!_font.loadFromFile("res/fonts/Pixellari.ttf")) {
        throw std::runtime_error("Impossible de lire la police de caractères.");
    }

    _text = sf::Text(sf::String(title), _font, 42);
    _callback = callback;
}

void MenuButton::onEvent(const sf::Event& event) {
    if(event.type == sf::Event::EventType::KeyPressed) {
        switch(event.key.code) {
            case sf::Keyboard::Key::Return:
                _callback();
        }
    }
}

void MenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_text, states);
}

sf::FloatRect MenuButton::bounds() const {
    sf::FloatRect bounds = _text.getLocalBounds();
    bounds.height = _text.getCharacterSize();
    return bounds;
}

sf::Vector2f MenuButton::position() const {
    return _text.getPosition();
}

void MenuButton::setPosition(const sf::Vector2f& position) {
    _text.setPosition(position);
}
