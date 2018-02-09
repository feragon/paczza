#pragma once

#include <ostream>

template<typename T = int>
class Position {
    public:
        T x;
        T y;

        /**
         * @brief Crée un nouveau point
         * @param x Abscisse du point
         * @param y Ordonnée du point
         */
        Position(const T& x = 0, const T& y = 0);

        template <typename U>
        Position(const Position<U>& p);

        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;

        Position operator + (const Position& other) const;
        Position operator - (const Position& other) const;
        Position operator * (double factor) const;
        Position operator + (T offset) const;
        Position operator - (T offset) const;

        template<typename osT>
        friend std::ostream& operator<<(std::ostream& os, const Position<osT>& position);
};

template<typename T>
Position<T>::Position(const T& x, const T& y) {
        this->x = x;
        this->y = y;
}

template <typename T>
template <typename U>
Position<T>::Position(const Position<U>& p) {
        x = p.x;
        y = p.y;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Position<T>& position) {
        os << "Position(" << position.x << ";" << position.y << ")";
        return os;
}

template<typename T>
bool Position<T>::operator==(const Position& other) const {
        return x == other.x &&
               y == other.y;
}

template<typename T>
bool Position<T>::operator!=(const Position& other) const {
        return !(other == *this);
}

template<typename T>
Position<T> Position<T>::operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
}

template<typename T>
Position<T> Position<T>::operator - (const Position& other) const {
    return Position(x - other.x, y - other.y);
}

template<typename T>
Position<T> Position<T>::operator * (double factor) const {
    return Position(x * factor, y * factor);
}

template<typename T>
Position<T> Position<T>::operator + (T offset) const {
    return Position(x + offset, y + offset);
}

template<typename T>
Position<T> Position<T>::operator - (T offset) const {
    return Position(x - offset, y - offset);
}
