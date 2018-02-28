#include "element.h"

Element::Element() {
    _position = nullptr;
}

std::string Element::toString() const {
    std::ostringstream oss;
    oss << "Element()";
    return oss.str();
}

Element::operator std::string() const {
    return toString();
}

std::ostream& operator<<(std::ostream& o, const Element* element) {
    o << element->toString();
    return o;
}
