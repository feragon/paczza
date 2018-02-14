#pragma once

#include <iostream>

template <typename T>
class SharedPtr {
    private:
        unsigned int* _count;
        T* _ptr;

    public:
        template <typename... Args>
        explicit SharedPtr(Args... args);

        SharedPtr(const SharedPtr<T>& other);

        virtual ~SharedPtr();

        SharedPtr<T>& operator = (const SharedPtr<T>& other);

        inline T* operator ->() const;
        inline T& operator *() const;
        inline T* get() const;
        inline unsigned int count() const;
};

template<typename T>
template<typename... Args>
SharedPtr<T>::SharedPtr(Args... args) {
    _count = new unsigned int;
    *_count = 1;

    _ptr = new T(args...);
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
    _count = other._count;
    _ptr = other._ptr;

    (*_count)++;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    (*_count)--;

    if((*_count) == 0) {
        delete _count;
        delete _ptr;
    }
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    (*_count)--;

    if((*_count) == 0) {
        delete _count;
        delete _ptr;
    }

    _count = other._count;
    _ptr = other._ptr;
    (*_count)++;
}

template<typename T>
T* SharedPtr<T>::operator->() const {
    return _ptr;
}

template<typename T>
T& SharedPtr<T>::operator*() const {
    return *_ptr;
}

template<typename T>
T* SharedPtr<T>::get() const {
    return _ptr;
}

template<typename T>
unsigned int SharedPtr<T>::count() const {
    return *_count;
}
