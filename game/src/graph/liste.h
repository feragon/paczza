#pragma once

#include <sstream>

template <typename T>
class Liste {
    public:
        Liste<T>* next;
        T* value;

        Liste(T* v = nullptr, Liste<T>* n = nullptr) {
            next = n;
            value = v;
        }

        static int taille(const Liste<T> * l);

        static std::string toString(const Liste<T>* l,
                                    const char* debut="(",
                                    const char* separateur = ", ",
                                    const char* fin=")"
        );

        static void insertionOrdonnee(T* a,
                                      Liste<T>*& l,
                                      bool (*estPlusPetitOuEgal)(const T* a1, const T* a2)
        );

        static T* depiler(Liste<T>*& l);

        static bool retire(const T * a, Liste<T> * & l);

        static void efface1(Liste<T>*& l);

        static void efface2(Liste<T>*& l);

        static Liste<T>* copie1(Liste<T> * l);
        static Liste<T>* copie2(Liste<T> * l);
        static Liste<T>* copie3(Liste<T> * l);

        static Liste<T>* appartient(const T* a,  Liste<T>* l);

        template <class FONCTEUR>
        static Liste<T>* appartient(Liste<T>* l, const FONCTEUR& condition);
};

template <typename T>
int Liste<T>::taille(const Liste<T>* l) {
    int taille = 0;

    while(l) {
        taille++;
        l = l->next;
    }

    return taille;
}

template <typename T>
std::string Liste<T>::toString(const Liste<T>* l, const char* debut, const char* separateur, const char* fin) {
    std::ostringstream oss;
    oss << debut;

    if(l) {
        oss << *(l->value);
        l = l->next;
    }
    while(l) {
        oss << separateur;
        oss << *(l->value);
        l = l->next;
    }

    oss << fin;
    return oss.str();
}

template <typename T>
void Liste<T>::insertionOrdonnee(T* a, Liste<T>*& l, bool (*estPlusPetitOuEgal)(const T*, const T*)) {
    if(!l || estPlusPetitOuEgal(a, l->value)) {
        l = new Liste<T>(a, l);
    }
    else {
        Liste<T>::insertionOrdonnee(a, l->next, estPlusPetitOuEgal);
    }
}

template <typename T>
T* Liste<T>::depiler(Liste<T>*& l) {
    if(!l) {
        throw std::invalid_argument("Impossible de déplier une pile vide");
    }

    T* value = l->value;
    Liste<T>* firstElement = l;
    l = l->next;

    delete firstElement;

    return value;
}

template <typename T>
bool Liste<T>::retire(const T* a, Liste<T>*& l) {
    if(!l) {
        return false;
    }

    if(l->value == a) {
        Liste<T>* element = l;
        l = l->next;
        delete element;

        return true;
    }
    else {
        return Liste<T>::retire(a, l->next);
    }
}

template <typename T>
void Liste<T>::efface1(Liste<T>*& l) {
    if(!l) {
        return;
    }

    Liste<T>::efface1(l->next);
    delete l;
    l = nullptr;
}

template <typename T>
void Liste<T>::efface2(Liste<T>*& l) {
    if(!l) {
        return;
    }

    Liste<T>::efface2(l->next);
    delete l->value;
    delete l;
    l = nullptr;
}

template <typename T>
Liste<T>* Liste<T>::copie1(Liste<T>* l) {
    if(!l) {
        return nullptr;
    }

    return new Liste<T>(l->value, Liste<T>::copie1(l->next));
}

template <typename T>
Liste<T>* Liste<T>::copie2(Liste<T>* l) {
    if(!l) {
        return nullptr;
    }

    return new Liste<T>(new T(*(l->value)), Liste<T>::copie2(l->next));
}

template <typename T>
Liste<T>* Liste<T>::copie3(Liste<T>* l) {
    if(!l) {
        return nullptr;
    }

    return new Liste<T>(l->value->copie(), Liste<T>::copie3(l->next));
}

template <typename T>
Liste<T>* Liste<T>::appartient(const T* a, Liste<T>* l) {
    while(l) {
        if(l->value == a) {
            return l;
        }

        l = l->next;
    }

    return nullptr;
}

template<typename T>
template<typename FONCTEUR>
Liste<T>* Liste<T>::appartient(Liste<T>* l, const FONCTEUR& condition){
    while(l) {
        if(condition(l->value)) {
            return l;
        }

        l = l->next;
    }

    return nullptr;
}