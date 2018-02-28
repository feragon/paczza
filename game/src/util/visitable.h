#pragma once

template <typename T>
class Visitable {
    public:
        virtual void accept(T& visitor) = 0;
};