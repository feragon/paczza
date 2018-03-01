#pragma once

#include <stdexcept>

class UnknownCommand : public std::runtime_error {
    public:
        /**
         * @brief Exception lancée lorsque la commande de l'utilisateur n'est pas reconnue
         * @param m Message
         */
        UnknownCommand(const char* m) : runtime_error(m) {

        }
};