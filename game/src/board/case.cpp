#include "case.h"

Case::Case() {

}

Case::~Case() {

}

std::ostream & operator<<(std::ostream &os, const Case& s) {
    os << "Case()";
    return os;
}