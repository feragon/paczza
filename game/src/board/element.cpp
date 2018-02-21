#include "element.h"

Element::Element(Sprite sprite, Sound sound) :
        _sprite(sprite), _sound(sound) {

}

std::string Element::toString() const {
    std::ostringstream oss;
    oss << "Element(_sprite:" << _sprite << "; _sound=" << _sound << ")";
    return oss.str();
}

Element::operator std::string() const {
    return toString();
}

std::ostream& operator<<(std::ostream& o, const Element* element) {
    o << element->toString();
    return o;
}
