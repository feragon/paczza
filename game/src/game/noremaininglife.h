#pragma once

#include <stdexcept>

class NoRemainingLife : public std::runtime_error {
    public:
        /**
         * @brief Exception utilisée lorsque le joueur a utilisé toutes ses vies
         * @param message Message
         */
        NoRemainingLife(const char* message) : runtime_error(message) {

        }
};