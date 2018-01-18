#pragma once

#include <ostream>

class Case {
    private:
        int _points;
    public:
        Case();
        virtual ~Case();

        int eatGum();

        friend std::ostream& operator<<(std::ostream &, const Case&);
};