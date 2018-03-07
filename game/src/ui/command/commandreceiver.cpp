#include "commandreceiver.h"

void CommandReceiver::setKeyPressedCommand(const sf::Keyboard::Key& key, SharedPtr<Command> command) {
    _keyPressedCommands.insert(std::pair<sf::Keyboard::Key, SharedPtr<Command>>(key, command));
}

void CommandReceiver::removeKeyPressedCommand(const sf::Keyboard::Key& key) {
    _keyPressedCommands.erase(key);
}

SharedPtr<const Command> CommandReceiver::getKeyPressedCommand(const sf::Keyboard::Key& key) const {
    try {
        return _keyPressedCommands.at(key);
    }
    catch (std::out_of_range& e) {
        throw UnknownCommand("Commande inconnue");
    }
}

void CommandReceiver::setKeyReleasedCommand(const sf::Keyboard::Key& key, SharedPtr<Command> command) {
    _keyReleasedCommands.insert(std::pair<sf::Keyboard::Key, SharedPtr<Command>>(key, command));
}

void CommandReceiver::removeKeyReleasedCommand(const sf::Keyboard::Key& key) {
    _keyReleasedCommands.erase(key);
}

SharedPtr<const Command> CommandReceiver::getKeyReleasedCommand(const sf::Keyboard::Key& key) const {
    try {
        return _keyReleasedCommands.at(key);
    }
    catch (std::out_of_range& e) {
        throw UnknownCommand("Commande inconnue");
    };
}

void CommandReceiver::manageEvent(const sf::Event& event) const {
    try {
        if(event.type == sf::Event::KeyPressed) {
            _keyPressedCommands.at(event.key.code)->execute();
            return;
        }
        if(event.type == sf::Event::KeyReleased) {
            _keyReleasedCommands.at(event.key.code)->execute();
            return;
        }
    }
    catch (std::out_of_range& e) {
        throw UnknownCommand("Commande inconnue");
    }

    throw UnknownCommand("Commande inconnue");
}