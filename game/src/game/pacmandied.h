#pragma once

#include <stdexcept>

class PacmanDied : public std::runtime_error {
    public:
        /**
         * @brief Exception lancée lorsque le joueur meurt
         * @param m Message
         */
        PacmanDied(const char* m) : runtime_error(m) {

        }
};