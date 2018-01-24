#pragma once

#include <stdexcept>

class NoRemainingLife : public std::runtime_error {
    public:
        NoRemainingLife(const char* message) : runtime_error(message) {

        }
};