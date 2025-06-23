#pragma once
#include <cstdint>
#include <iostream>

constexpr float GROWTH_FACTOR = 2.0f;

template <typename T>
class ArrayList
{
private:
    T* m_array;
    size_t m_capacity;
    size_t m_size;

public:
    ArrayList();                                // Default ctor
    ArrayList(const ArrayList<T>& copy);        // Copy
    ArrayList<T>& operator=(ArrayList<T> obj);  // Copy assignment
    ~ArrayList();                               // Delete

    void insertAtStart(T value);
    void insertAtEnd(T value);
    void insertBeforeIndex(size_t index, T value);
    void insertAfterIndex(size_t index, T value);
    void insertBeforeKey(T key, T value);
    void insertAfterKey(T key, T value);
    void update(size_t index, T value);
    void update(T key, T value);

    void removeFirst();
    void removeLast();
    void removeAtIndex(size_t index);
    void removeAtKey (T key);
    void clear();

    size_t find(T key) const;
    size_t capacity() const;
    size_t size() const;
    void print();
    void swap(ArrayList<T>& obj1, ArrayList<T>& obj2);

    T operator[](size_t index) const;
    bool operator==(const ArrayList<T>& obj) const;
};

template<typename T>
inline ArrayList<T>::ArrayList()
{
    m_capacity = 1;
    m_size = 0;
    m_array = new T[m_capacity];
}

template<typename T>
inline ArrayList<T>::ArrayList(const ArrayList<T>& copy)
{
    if (this == &copy)
        return;

    this->m_capacity = copy.m_capacity;
    this->m_size = copy.m_size;
    this->m_array = new T[m_capacity];

    for (size_t i = 0; i < m_size; ++i)
        this->m_array[i] = copy.m_array[i];
}

template<typename T>
inline ArrayList<T>& ArrayList<T>::operator=(ArrayList<T> obj)
{
    if (this == &obj)
        return *this;

    swap(*this, obj);

    return *this;
}

template<typename T>
inline ArrayList<T>::~ArrayList()
{
    delete[] m_array;
}

template<typename T>
inline void ArrayList<T>::insertAtStart(T value)
{
    if (m_size == m_capacity)
    {
        m_capacity = size_t(m_capacity * GROWTH_FACTOR);

        T* old = m_array;
        m_array = new T[m_capacity];

        for (size_t i = 0; i < m_size; ++i)
            m_array[i + 1] = old[i];

        delete[] old;
    }
    else
    {
        // Shifting array to right
        for (size_t i = m_size; i > 0; --i)
            m_array[i] = m_array[i - 1];
    }

    m_array[0] = value;
    m_size += 1;
}

template<typename T>
inline void ArrayList<T>::insertAtEnd(T value)
{
    if (m_size == m_capacity)
    {
        m_capacity = size_t(m_capacity * GROWTH_FACTOR);

        T* old = m_array;
        m_array = new T[m_capacity];

        for (size_t i = 0; i < m_size; ++i)
            m_array[i] = old[i];

        delete[] old;
    }

    m_array[m_size] = value;
    m_size += 1;
}

template<typename T>
inline void ArrayList<T>::insertBeforeIndex(size_t index, T value)
{
    if (index > m_size)
        throw std::out_of_range("Index out of bounds");

    if (index == 0)
    {
        insertAtStart(value);
        return;
    }

    if (index == m_size)
    {
        insertAtEnd(value);
        return;
    }

    if (m_size == m_capacity)
    {
        m_capacity = size_t(m_capacity * GROWTH_FACTOR);

        T* old = m_array;
        m_array = new T[m_capacity];

        for (size_t i = 0; i < index; ++i)
            m_array[i] = old[i];

        m_array[index] = value;
        
        for (size_t i = index; i < m_size; ++i)
            m_array[i + 1] = old[i];

        m_size += 1;
        delete[] old;

        return;
    }

    for (size_t i = m_size; i > index; --i)
        m_array[i] = m_array[i - 1];

    m_array[index] = value;
    m_size += 1;
}

template<typename T>
inline void ArrayList<T>::insertAfterIndex(size_t index, T value)
{
    insertBeforeIndex(index + 1, value);
}

template<typename T>
inline void ArrayList<T>::insertBeforeKey(T key, T value)
{
    size_t index = find(key);

    if (index == m_size)
        return;

    insertBeforeIndex(index, value);
}

template<typename T>
inline void ArrayList<T>::insertAfterKey(T key, T value)
{
    size_t index = find(key);

    if (index == m_size)
        return;

    insertAfterIndex(index, value);
}

template<typename T>
inline void ArrayList<T>::update(size_t index, T value)
{
    m_array[index] = value;
}

template<typename T>
inline void ArrayList<T>::update(T key, T value)
{
    size_t index = find(key);
    m_array[index] = value;
}

template<typename T>
inline void ArrayList<T>::removeFirst()
{
    if (m_size == 0)
        return;

    for (size_t i = 0; i < m_size - 1; ++i)
        m_array[i] = m_array[i + 1];

    m_size -= 1;
}

template<typename T>
inline void ArrayList<T>::removeLast()
{
    if (m_size == 0)
        return;

    m_size -= 1;
}

template<typename T>
inline void ArrayList<T>::removeAtIndex(size_t index)
{
    if (index >= m_size)
        throw std::out_of_range("Index out of bounds");

    if (index == 0)
    {
        removeFirst();
        return;
    }

    if (index == m_size - 1)
    {
        removeLast();
        return;
    }

    m_size -= 1;
    for (size_t i = index; i < m_size; ++i)
        m_array[i] = m_array[i + 1];
}

template<typename T>
inline void ArrayList<T>::removeAtKey(T key)
{
    size_t index = find(key);
    if (index == m_size)
        return;

    removeAtIndex(index);
}

template<typename T>
inline void ArrayList<T>::clear()
{
    m_size = 0;
}

template<typename T>
inline T ArrayList<T>::operator[](size_t index) const
{
    if (index >= m_size)
        throw std::out_of_range("Index out of range");

    return m_array[index];
}

template<typename T>
inline bool ArrayList<T>::operator==(const ArrayList<T>& obj) const
{
    if (this->m_size != obj.m_size)
        return false;

    for (size_t i = 0; i < m_size; ++i)
    {
        if (this->m_array[i] != obj.m_array[i])
            return false;
    }
    
    return true;
}

template<typename T>
inline size_t ArrayList<T>::find(T key) const
{
    size_t index = m_size;
    for (size_t i = 0; i < m_size; ++i)
    {
        if (m_array[i] == key)
        {
            index = i;
            break;
        }
    }

    return index;
}

template<typename T>
inline size_t ArrayList<T>::capacity() const
{
    return m_capacity;
}

template<typename T>
inline size_t ArrayList<T>::size() const
{
    return m_size;
}

template<typename T>
inline void ArrayList<T>::print()
{
    for (size_t i = 0; i < m_size; ++i)
        std::cout << m_array[i] << ' ';
}

template<typename T>
inline void ArrayList<T>::swap(ArrayList<T>& obj1, ArrayList<T>& obj2)
{
    using std::swap;
    swap(obj1.m_capacity, obj2.m_capacity);
    swap(obj1.m_size, obj2.m_size);
    swap(obj1.m_array, obj2.m_array);
}
