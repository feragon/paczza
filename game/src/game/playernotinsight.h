#pragma once

#include <stdexcept>

class PlayerNotInSight : public std::runtime_error {
    public:
        PlayerNotInSight(const char* message) :
                runtime_error(message) {

        }
};