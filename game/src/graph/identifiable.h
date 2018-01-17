#pragma once

#include <string>

class Identifiable {
    private:
        int _cle;

    public:
        Identifiable(int cle);

        inline int cle() const;
        inline void setCle(int cle);

        operator std::string() const;
        friend std::ostream& operator << (std::ostream& o, const Identifiable& i);
};

int Identifiable::cle() const {
    return _cle;
}

void Identifiable::setCle(int cle) {
    _cle = cle;
}