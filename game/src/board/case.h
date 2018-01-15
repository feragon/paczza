#pragma once

#include <ostream>

class Case {
    private:

    public:
        Case();
        virtual ~Case();

        friend std::ostream& operator<<(std::ostream &, const Case&);
};