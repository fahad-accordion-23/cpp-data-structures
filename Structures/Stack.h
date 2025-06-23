#pragma once
#include <cstdint>
#include <iostream>
#include "ArrayList.h"

/*
 * Stack is implemented using the array list created in LAB 01
 * Stack is dynamically resizing
 */

template <typename T>
class Stack : private ArrayList<T>
{
private:

public:
    Stack() = default;
    Stack(const Stack<T>& copy);
    Stack<T>& operator=(Stack<T> obj);
    ~Stack() = default;

    void push(T value);
    T pop();
    T top();
    bool isEmpty();
    bool isFull();

    size_t size();

    void print();
};

template<typename T>
inline Stack<T>::Stack(const Stack<T>& copy)
    : ArrayList<T>(copy)
{
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(Stack<T> obj)
{
    ArrayList<T>::operator=(obj);

    return *this;
}

template<typename T>
inline void Stack<T>::push(T value)
{
    ArrayList<T>::insertAtEnd(value);
}

template<typename T>
inline T Stack<T>::pop()
{
    size_t _size = ArrayList<T>::size();

    if (_size == 0)
        return T();

    T temp = ArrayList<T>::operator[](_size - 1);
    ArrayList<T>::removeLast();

    return temp;
}

template<typename T>
inline T Stack<T>::top()
{
    if (ArrayList<T>::size() != 0)
        return ArrayList<T>::operator[](ArrayList<T>::size() - 1);

    return T();
}

template<typename T>
inline bool Stack<T>::isEmpty()
{
    if (ArrayList<T>::size() == 0)
        return true;
    else
        return false;
}

template<typename T>
inline bool Stack<T>::isFull()
{
    return !isEmpty();
}

template<typename T>
inline size_t Stack<T>::size()
{
    return ArrayList<T>::size();
}

template<typename T>
inline void Stack<T>::print()
{
    ArrayList<T>::print();
}