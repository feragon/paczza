#pragma once

#include <stdexcept>

class NoMoreLevels : public std::runtime_error {
    public:
        /**
         * @brief Exception utilisée lorsqu'il n'y a plus de niveau disponible
         */
        NoMoreLevels() : runtime_error("Il n'y a plus de niveau disponible") {

        }
};