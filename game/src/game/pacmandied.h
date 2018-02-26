#pragma once

#include <stdexcept>

class PacmanDied : public std::runtime_error {
    public:
        PacmanDied(const char* m) : runtime_error(m) {

        }
};