#pragma once

#include <graph/liste.h>

template <typename Listener>
class Listened {
    private:
        Listened<Listener>& operator = (const Listened<Listener>&);

        Liste<Listener>* _listeners;

    public:
        /**
         * @brief Classe qui se fait écouter
         */
        Listened();
        virtual ~Listened();
        Listened(const Listened<Listener>& listened);

        /**
         * @brief Ajoute un écouteur
         * @param listener Nouvel écouteur
         */
        void addListener(Listener* listener);

        /**
         * @brief Enlève un écouteur
         * @param listener Écouteur
         */
        void removeListener(Listener* listener);

        /**
         * @brief Appelle tous les écouteurs
         * @tparam FunctionPointer Type de fonction à appeler
         * @tparam Args Type des arguments
         * @param fp Pointeur sur la fonction
         * @param args Arguments
         */
        template <typename FunctionPointer, typename... Args>
        void callListeners(FunctionPointer fp, Args... args);
};

template<typename Listener>
Listened<Listener>::Listened() {
    _listeners = nullptr;
}

template<typename Listener>
Listened<Listener>::~Listened() {
    Liste<Listener>::efface1(_listeners);
}

template<typename Listener>
Listened<Listener>::Listened(const Listened<Listener>& listened) : Listened() {
}

template<typename Listener>
void Listened<Listener>::addListener(Listener* listener) {
    _listeners = new Liste<Listener>(listener, _listeners);
}

template<typename Listener>
void Listened<Listener>::removeListener(Listener* listener) {
    Liste<Listener>::retire(listener, _listeners);
}

template<typename Listener>
template<typename FunctionPointer, typename... Args>
void Listened<Listener>::callListeners(FunctionPointer fp, Args... args) {
    for(Liste<Listener>* listeners = _listeners; listeners; listeners = listeners->next) {
        (listeners->value->*fp)(args...);
    }
}
