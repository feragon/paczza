#include <ui/resourceloader.h>
#include "case.h"

Case::Case(const Position<>& position, const Element* element) {
    _position = position;
    _element = nullptr;

    setElement(element);
}

Case::Case(const Case& c) : InfoSommet(c) {
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

Case::operator std::string() const {
    std::ostringstream oss;
    oss << (*this);
    return oss.str();
}

void Case::setElement(const Element* element) {
    if(_element) {
        delete _element;
    }

    if(element) {
        _element = element->clone();
        _element->setPosition(this);
    }
    else {
        _element = nullptr;
    }
}