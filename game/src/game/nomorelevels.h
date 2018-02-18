#pragma once

#include <stdexcept>

class NoMoreLevels : public std::runtime_error {
    public:
        NoMoreLevels() : runtime_error("Il n'y a plus de niveau disponible") {

        }
};