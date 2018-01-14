#pragma once

#include <ostream>

template <class S>
class ElementSommet {
private:
    ElementSommet<S> *_suivant;
    S *_dataSommet;

public:
    ElementSommet(S *dataSommet, ElementSommet<S> *suivant);
};


template <class S>
ElementSommet<S>::ElementSommet(S *dataSommet, ElementSommet<S> *suivant) {
    this->_dataSommet = dataSommet;
    this->_suivant = suivant;
}