#pragma once

#include <cstdint>
#include <iostream>

template<typename T>
class SinglyLinkedList
{
protected:
    struct Node
    {
        T data;
        Node* next;

        Node() : data(T()), next(nullptr) {}
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;

    Node* getNodeByIndex(size_t index) const;
    Node* getNodeByKey(T key) const;

    void insertAfterNode(Node* node, T value);
    void removeNextNode(Node* node);
    void _printReversed(Node* node);

public:
    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList<T>& copy);
    SinglyLinkedList<T>& operator=(SinglyLinkedList<T>& obj);
    ~SinglyLinkedList();


    void insertAtStart(T value);
    void insertAtEnd(T value);
    void insertBeforeIndex(size_t index, T value);
    void insertAfterIndex(size_t index, T value);
    void insertBeforeKey(T key, T value);
    void insertAfterKey(T key, T value);
    void updateIndex(size_t index, T value);
    void updateKey(T key, T value);

    void removeFirst();
    void removeLast();
    void removeAtIndex(size_t index);
    void removeAtKey(T key);
    void clear();

    void swap(size_t l_index, size_t r_index);

    size_t find(T key) const;
    size_t size() const;
    bool isEmpty() const;
    void print();
    void printReversed();
    static void swap(SinglyLinkedList<T>& obj1, SinglyLinkedList<T>& obj2);

    T operator[](size_t index) const;
};

template<typename T>
inline SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNodeByIndex(size_t index) const
{
    if (index >= m_size)
    {
        throw std::out_of_range("index out of bounds");
    }

    Node* temp = m_head;
    for (size_t i = 0; i < index; ++i)
    {
        temp = temp->next;
    }

    return temp;
}

template<typename T>
inline SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNodeByKey(T key) const
{
    Node* temp = m_head;
    for (size_t i = 0; i < m_size; ++i)
    {
        if (temp->data == key)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }

    return nullptr;
}

template<typename T>
inline void SinglyLinkedList<T>::insertAfterNode(Node* node, T value)
{
    Node* new_node = new Node;
    new_node->data = value;
    new_node->next = node->next;
    node->next = new_node;
    ++m_size;
}

template<typename T>
inline void SinglyLinkedList<T>::removeNextNode(Node* node)
{
    Node* dead = node->next;
    node->next = dead->next;
    delete dead;
    --m_size;
}

template<typename T>
inline SinglyLinkedList<T>::SinglyLinkedList()
    : m_head(nullptr), m_tail(nullptr), m_size(0)
{
}

template<typename T>
inline SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& copy)
{
    Node* temp = copy.m_head;
    for (size_t i = 0; i < copy.m_size; ++i)
    {
        insertAtEnd(temp->data);
        temp = temp->next;
    }
}

template<typename T>
inline SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>& obj)
{
    swap(*this, obj);
    return *this;
}

template<typename T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
{
    if (!m_head)
    {
        return;
    }

    Node* curr = m_head;
    Node* temp;
    while (curr != nullptr)
    {
        temp = curr->next;
        delete curr;
        curr = temp;
    }
}

template<typename T>
inline void SinglyLinkedList<T>::insertAtStart(T value)
{
    Node* new_node = new Node;
    new_node->data = value;
    ++m_size;
    new_node->next = m_head;
    m_head = new_node;

    if (m_head == nullptr)
    {
        m_tail = new_node;
    }
}

template<typename T>
inline void SinglyLinkedList<T>::insertAtEnd(T value)
{
    Node* new_node = new Node;
    new_node->data = value;
    ++m_size;

    if (m_tail == nullptr)
    {
        m_head = new_node;
        m_tail = new_node;

        return;
    }

    m_tail->next = new_node;
    m_tail = new_node;
}

template<typename T>
inline void SinglyLinkedList<T>::insertBeforeIndex(size_t index, T value)
{
    if (index == 0)
    {
        insertAtStart(value);
        return;
    }

    Node* temp = getNodeByIndex(index - 1);
    insertAfterNode(temp, value);
}

template<typename T>
inline void SinglyLinkedList<T>::insertAfterIndex(size_t index, T value)
{
    if (index == m_size - 1)
    {
        insertAtEnd(value);
        return;
    }

    Node* temp = getNodeByIndex(index);
    insertAfterNode(temp, value);
}

template<typename T>
inline void SinglyLinkedList<T>::insertBeforeKey(T key, T value)
{
    if (m_head->data == key)
    {
        insertAtStart(value);
    }

    Node* temp = m_head;

    while (temp != nullptr && temp->next->data != key)
    {
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        insertAtEnd(value);
        return;
    }

    insertAfterNode(temp, value);
}

template<typename T>
inline void SinglyLinkedList<T>::insertAfterKey(T key, T value)
{
    if (m_tail->data == key)
    {
        insertAtEnd(value);
    }

    Node* temp = m_head;

    while (temp != nullptr && temp->data != key)
    {
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        insertAtEnd(value);
        return;
    }

    insertAfterNode(temp, value);
}

template<typename T>
inline void SinglyLinkedList<T>::updateIndex(size_t index, T value)
{
    Node* temp = getNodeByIndex(index);
    temp->data = value;
}

template<typename T>
inline void SinglyLinkedList<T>::updateKey(T key, T value)
{
    Node* temp = getNodeByKey(key);
    if (temp != nullptr)
        temp->data = value;
}

template<typename T>
inline void SinglyLinkedList<T>::removeFirst()
{
    if (isEmpty())
    {
        return;
    }

    if (m_head == m_tail)
        m_tail = nullptr;

    Node* temp = m_head;
    m_head = m_head->next;
    delete temp;
    --m_size;
}

template<typename T>
inline void SinglyLinkedList<T>::removeLast()
{
    if (isEmpty())
    {
        return;
    }

    if (m_head == m_tail)
        m_head = nullptr;

    Node* second_last = getNodeByIndex(m_size - 1);
    delete second_last->next;
    second_last->next = nullptr;
    m_tail = second_last;
    --m_size;
}

template<typename T>
inline void SinglyLinkedList<T>::removeAtIndex(size_t index)
{
    if (index == 0)
    {
        removeFirst();
        return;
    }
    else if (index == m_size - 1)
    {
        removeLast();
        return;
    }

    Node* temp = getNodeByIndex(index - 1);
    removeNextNode(temp);
}

template<typename T>
inline void SinglyLinkedList<T>::removeAtKey(T key)
{
    if (m_head->data == key)
    {
        removeFirst();
        return;
    }
    else if (m_tail->data == key)
    {
        removeLast();
        return;
    }

    Node* temp = m_head;

    while (temp != nullptr && temp->next->data != key)
    {
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        insertAtEnd(key);
        return;
    }

    removeNextNode(temp);
}

template<typename T>
inline void SinglyLinkedList<T>::clear()
{
    SinglyLinkedList<T> empty;
    swap(*this, empty);
} // Empty will be destroyed here which will clean up the memory

template<typename T>
inline void SinglyLinkedList<T>::swap(size_t l_index, size_t r_index)
{
    Node* l_prev, * l, * r_prev, * r;

    if (l_index == 0)
    {
        l_prev = nullptr;
        l = m_head;
    }
    else
    {
        l_prev = getNodeByIndex(l_index - 1);
        l = l_prev->next;
    }

    r_prev = getNodeByIndex(r_index - 1);
    r = r_prev->next;

    if (l_prev)
        l_prev->next = r;

    r_prev->next = l;

    Node* temp = l->next;
    l->next = r->next;
    r->next = temp;
}

template<typename T>
inline size_t SinglyLinkedList<T>::find(T key) const
{
    Node* temp = m_head;
    for (size_t i = 0; i < m_size; ++i)
    {
        if (temp->data == key)
        {
            return i;
        }
        else
        {
            temp = temp->next;
        }
    }

    return m_size + 1;
}

template<typename T>
inline size_t SinglyLinkedList<T>::size() const
{
    return m_size;
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() const
{
    return m_head == nullptr;
}

template<typename T>
inline void SinglyLinkedList<T>::print()
{
    if (isEmpty())
        return;

    Node* temp = m_head;
    while (temp != nullptr)
    {
        std::cout << temp->data << ' ';
        temp = temp->next;
    }
}

template<typename T>
inline void SinglyLinkedList<T>::_printReversed(Node* node)
{
    if (node == nullptr)
        return;

    _printReversed(node->next);
    std::cout << node->data << ' ';
}

template<typename T>
inline void SinglyLinkedList<T>::printReversed()
{
    _printReversed(m_head);
}

template<typename T>
inline void SinglyLinkedList<T>::swap(SinglyLinkedList<T>& obj1, SinglyLinkedList<T>& obj2)
{
    using std::swap;
    swap(obj1.m_head, obj2.m_head);
    swap(obj1.m_tail, obj2.m_tail);
    swap(obj1.m_size, obj2.m_size);
}

template<typename T>
inline T SinglyLinkedList<T>::operator[](size_t index) const
{
    return getNodeByIndex(index)->data;
}