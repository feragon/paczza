#pragma once

#include "command.h"
#include "unknowncommand.h"
#include <map>
#include <util/shared_ptr.h>

template <typename T>
class CommandReceiver {
    public:
        /**
         * @brief Définit une commande
         * @param key Identifiant de la commande
         * @param command Commande à exécuter
         */
        void setCommand(const T& key, SharedPtr<Command> command);

        /**
         * @brief Supprime une commande
         * @param key Identifiant de la commande
         */
        void removeCommand(const T& key);

        /**
         * @brief Donne une commande enregistrée
         * @param key Identifiant de la commande
         * @return Commade
         * @throw UnknownCommand si la commande n'existe pas
         */
        SharedPtr<const Command> getCommand(const T& key) const;

        /**
         * @brief Exécute une commande
         * @param key Identifiant de la commande
         * @throw UnknownCommand si la commande n'existe pas
         */
        void trigger(const T& key) const;

    private:
        std::map<T, SharedPtr<Command>> _commands;
};

template<typename T>
void CommandReceiver<T>::setCommand(const T& key, SharedPtr<Command> command) {
    _commands.insert(std::pair<T, SharedPtr<Command>>(key, command));
}

template<typename T>
void CommandReceiver<T>::removeCommand(const T& key) {
    _commands.erase(key);
}

template<typename T>
SharedPtr<const Command> CommandReceiver<T>::getCommand(const T& key) const {
    try {
        return _commands.at(key);
    }
    catch (std::out_of_range& e) {
        throw UnknownCommand("Commande inconnue");
    }
}

template<typename T>
void CommandReceiver<T>::trigger(const T& key) const {
    try {
        return _commands.at(key)->execute();
    }
    catch (std::out_of_range& e) {
        throw UnknownCommand("Commande inconnue");
    }
}
