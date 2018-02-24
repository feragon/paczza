#pragma once

#include <iostream>

template <typename T>
class SharedPtr {
    template<typename U>
    friend class SharedPtr;

    private:
        template <typename U>
        void copy(const SharedPtr<U>& other);
        void release();

        unsigned int* _count;
        T* _ptr;

    public:
        template <typename... Args>
        explicit SharedPtr(Args... args);

        explicit SharedPtr(nullptr_t);

        SharedPtr(const SharedPtr& other);
        template <typename U>
        SharedPtr(const SharedPtr<U>& other);

        virtual ~SharedPtr();

        SharedPtr<T>& operator = (nullptr_t other);
        SharedPtr<T>& operator = (const SharedPtr& other);
        template <typename U>
        SharedPtr<T>& operator = (const SharedPtr<U>& other);

        inline T* operator ->() const;
        inline T& operator *() const;
        inline T* get() const;
        inline unsigned int count() const;

        template <typename U>
        bool operator == (const U* other) const;

        operator bool() const;
};

template<typename T>
template<typename... Args>
SharedPtr<T>::SharedPtr(Args... args) {
    _count = new unsigned int;
    *_count = 1;

    _ptr = new T(args...);
}

template<typename T>
SharedPtr<T>::SharedPtr(nullptr_t) {
    _count = new unsigned int(1);
    _ptr = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
    copy(other);
}

template<typename T>
template <typename U>
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other) {
    copy(other);
}



template<typename T>
SharedPtr<T>::~SharedPtr() {
    release();
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    release();
    copy(other);
}

template<typename T>
template<typename U>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U>& other) {
    release();
    copy(other);
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

template<typename T>
template<typename U>
void SharedPtr<T>::copy(const SharedPtr<U>& other) {
    _count = other._count;
    _ptr = static_cast<T*>(other._ptr);

    (*_count)++;
}

template<typename T>
void SharedPtr<T>::release() {
    (*_count)--;

    if((*_count) == 0) {
        delete _count;
        delete _ptr;
    }
}

template<typename T>
template<typename U>
bool SharedPtr<T>::operator==(const U* other) const {
    return _ptr == other;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(nullptr_t other) {
    release();
    _ptr = nullptr;
    _count = new unsigned int(1);
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return (bool) _ptr;
}
