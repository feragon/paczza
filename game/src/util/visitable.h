#pragma once

template <typename T>
class Visitable {
    public:
        /**
         * @brief Accepte un visiteur
         * @param visitor Visiteur
         */
        virtual void accept(T& visitor) = 0;
};