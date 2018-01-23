#pragma once

#include <stdexcept>

class NoHeatedEdgeFound : public std::runtime_error {
    public:
        NoHeatedEdgeFound(const char* message) : runtime_error(message) {

        }
};