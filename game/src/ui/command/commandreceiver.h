#pragma once

#include "command.h"
#include "unknowncommand.h"
#include <map>
#include <util/shared_ptr.h>
#include <SFML/Window/Event.hpp>

class CommandReceiver {
    public:
        /**
         * @brief Définit une commande lors de l'appui d'une touche
         * @param key Identifiant de la commande
         * @param command Commande à exécuter
         */
        void setKeyPressedCommand(const sf::Keyboard::Key& key, SharedPtr<Command> command);

        /**
         * @brief Supprime une commande lors de l'appui d'une touche
         * @param key Identifiant de la commande
         */
        void removeKeyPressedCommand(const sf::Keyboard::Key& key);

        /**
         * @brief Donne une commande enregistrée lors de l'appui d'une touche
         * @param key Identifiant de la commande
         * @return Commade
         * @throw UnknownCommand si la commande n'existe pas
         */
        SharedPtr<const Command> getKeyPressedCommand(const sf::Keyboard::Key& key) const;

        /**
         * @brief Définit une commande lors du relâchement d'une touche
         * @param key Identifiant de la commande
         * @param command Commande à exécuter
         */
        void setKeyReleasedCommand(const sf::Keyboard::Key& key, SharedPtr<Command> command);

        /**
         * @brief Supprime une commande lors du relâchement d'une touche
         * @param key Identifiant de la commande
         */
        void removeKeyReleasedCommand(const sf::Keyboard::Key& key);

        /**
         * @brief Donne une commande enregistrée lors du relâchement d'une touche
         * @param key Identifiant de la commande
         * @return Commade
         * @throw UnknownCommand si la commande n'existe pas
         */
        SharedPtr<const Command> getKeyReleasedCommand(const sf::Keyboard::Key& key) const;

        /**
         * @brief Exécute la commande correspondant à l'évènement reçu
         * @param event Evenement
         */
        void manageEvent(const sf::Event& event) const;

    private:
        std::map<sf::Keyboard::Key, SharedPtr<Command>> _keyPressedCommands;
        std::map<sf::Keyboard::Key, SharedPtr<Command>> _keyReleasedCommands;
};
