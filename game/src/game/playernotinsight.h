#pragma once

#include <stdexcept>

class PlayerNotInSight : public std::runtime_error {
    public:
        /**
         * @brief Exception lancée lorsque le joueur n'est pas à la vue du monstre
         * @param message Message
         */
        PlayerNotInSight(const char* message) :
                runtime_error(message) {

        }
};