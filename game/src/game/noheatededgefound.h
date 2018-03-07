#pragma once

#include <stdexcept>

class NoHeatedEdgeFound : public std::runtime_error {
    public:
        /**
         * @brief Exception utilisée lorsqu'aucune arête chaude est trouvée autour du monstre
         * @param message Message
         */
        NoHeatedEdgeFound(const char* message) : runtime_error(message) {

        }
};