#pragma once
#include <cstdint>
#include <iostream>

template<typename T>
class ArrayQueue
{
protected:
    T* m_data;
    size_t m_size;          // current size
    size_t m_capacity;
    size_t m_front;
    size_t m_rear;

public:
    ArrayQueue() = delete;
    ArrayQueue(size_t capacity);
    ArrayQueue(const ArrayQueue<T>& copy);
    ArrayQueue<T>& operator=(ArrayQueue<T> obj);
    ~ArrayQueue();

    void enqueue(T value);
    T dequeue();

    size_t size() const;
    bool isEmpty() const;
    void print();

    static void swap(ArrayQueue<T>& obj1, ArrayQueue<T>& obj2);
};

template<typename T>
inline ArrayQueue<T>::ArrayQueue(size_t capacity)
{
    m_data = new T[capacity];
    m_capacity = capacity;
    m_size = 0;
    m_front = capacity;         // if empty/invalid state then index = capacity
    m_rear = capacity;
}

template<typename T>
inline ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& copy)
{
    this->m_capacity = copy.m_capacity;
    this->m_size = copy.m_size;
    this->m_front = copy.m_front;
    this->m_rear = copy.m_rear;
    this->m_data = new T[m_capacity];

    for (size_t i = 0; i < m_size; ++i)
    {
        this->m_data[i] = copy.m_data[i];
    }
}

template<typename T>
inline ArrayQueue<T>& ArrayQueue<T>::operator=(ArrayQueue<T> obj)
{
    swap(*this, obj);
    return *this;
}

template<typename T>
inline ArrayQueue<T>::~ArrayQueue()
{
    delete[] m_data;
}

template<typename T>
inline void ArrayQueue<T>::enqueue(T value)
{
    if (m_size == m_capacity)
        return;

    // Check if first value being added
    if (m_front == m_capacity)
        m_front = 0;

    // Check if value being added will cause rear to wraparound
    m_rear += 1;
    if (m_rear >= m_capacity)
        m_rear = 0;

    m_data[m_rear] = value;
    m_size += 1;
}

template<typename T>
inline T ArrayQueue<T>::dequeue()
{
    // Check if empty
    if (m_size == 0)
        return T();

    T temp = m_data[m_front];

    if (m_front == m_rear)  // If the only remaining value is dequeud
    {
        m_front = m_capacity;
        m_rear = m_capacity;
        m_size = 1;
    }
    else
    {
        m_front += 1;
        
        if (m_front == m_capacity)
            m_front = 0;
    }

    m_size -= 1;
    return temp;
}

template<typename T>
inline size_t ArrayQueue<T>::size() const
{
    return m_size;
}

template<typename T>
inline bool ArrayQueue<T>::isEmpty() const
{
    return (m_size == 0);
}

template<typename T>
inline void ArrayQueue<T>::print()
{
    for (size_t i = 0, j = m_front; i < m_size; ++i, ++j)
    {
        if (j == m_capacity)
            j = 0;

        std::cout << m_data[j] << ' ';
    }

    std::cout << std::endl;
}

template<typename T>
inline void ArrayQueue<T>::swap(ArrayQueue<T>& obj1, ArrayQueue<T>& obj2)
{
    using std::swap;

    swap(obj1.m_capacity, obj2.m_capacity);
    swap(obj1.m_size, obj2.m_size);
    swap(obj1.m_data, obj2.m_data);
    swap(obj1.m_front, obj2.m_front);
    swap(obj1.m_rear, obj2.m_rear);
}