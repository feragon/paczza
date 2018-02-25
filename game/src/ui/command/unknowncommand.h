#pragma once

#include <stdexcept>

class UnknownCommand : public std::runtime_error {
    public:
        UnknownCommand(const char* m) : runtime_error(m) {

        }
};