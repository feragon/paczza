#include "case.h"

Case::Case(const Position<>& position, const Element* element) {
    _position = position;

    if(element) {
        _element = element->clone();
    }
    else {
        _element = nullptr;
    }
}

Case::Case(const Case& c) {
    copy(c);
}

Case& Case::operator=(const Case& c) {
    clear();
    copy(c);

    return *this;
}

Case::~Case() {
    clear();
}

void Case::copy(const Case& c) {
    _position = c._position;

    if(c._element) {
        _element = c._element->clone();
    }
    else {
        _element = c._element;
    }
}

void Case::clear() {
    if(_element) {
        delete _element;
    }

    _element = nullptr;
}

void Case::heberge(Pacman& joueur) {
    if(_element) {
        if(!_element->traversePar(joueur)) {
            delete _element;
            _element = nullptr;
        }
    }
}

std::ostream & operator<<(std::ostream &os, const Case& s) {
    os << "Case(" << s.position() << ")";
    return os;
}