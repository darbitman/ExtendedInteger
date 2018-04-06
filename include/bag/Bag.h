#pragma once

template<typename T>
class Bag {
private:
public:
    Bag();
    ~Bag();
    void add(T obj);
};


template<typename T>
Bag<T>::Bag() {
}


template<typename T>
Bag<T>::~Bag() {
}


template<typename T>
void Bag<T>::add(T obj) {
}