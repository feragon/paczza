#pragma once

#include <string>

class Identifiable {
    private:
        int _cle;

    public:
        /**
         * @brief Crée un élément identifiable
         * @param cle Clé
         */
        Identifiable(int cle);

        /**
         * @return Clé
         */
        inline int cle() const;

        /**
         * @brief Change la clé
         * @param cle Nouvelle clé
         */
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