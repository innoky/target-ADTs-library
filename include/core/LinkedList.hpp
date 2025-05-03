#pragma once

#include <stdexcept>
#include <vector>

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        T data;
        Node *next;

        Node(const T &data) : data(data), next(nullptr) {}
    };

private:
    Node *head;
    Node *tail;
    int size;

    void copyFrom(const LinkedList<T> &other)
    {
        Node *current = other.head;
        while (current)
        {
            Append(current->data);
            current = current->next;
        }
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

 
    LinkedList(const T *items, int count) : LinkedList()
    {
        for (int i = 0; i < count; ++i)
        {
            Append(items[i]);
        }
    }


    LinkedList(const LinkedList<T> &other) : LinkedList()
    {
        copyFrom(other);
    }


    ~LinkedList()
    {
        Clear();
    }

    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if (this != &other)
        {
            Clear();
            copyFrom(other);
        }
        return *this;
    }

    void Clear()
    {
        Node *current = head;
        while (current)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }


    T GetFirst() const
    {
        if (!head)
            throw std::out_of_range("List is empty");
        return head->data;
    }

    T GetLast() const
    {
        if (!tail)
            throw std::out_of_range("List is empty");
        return tail->data;
    }

    T Get(int index) const
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        Node *current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    int GetLength() const
    {
        return size;
    }

    Node *GetHead() const
    {
        return head;
    }

    void Append(const T &item)
    {
        Node *newNode = new Node(item);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void Prepend(const T &item)
    {
        Node *newNode = new Node(item);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        ++size;
    }

    void InsertAt(const T &item, int index)
    {
        if (index < 0 || index > size)
            throw std::out_of_range("Index out of range");
        if (index == 0)
        {
            Prepend(item);
            return;
        }
        if (index == size)
        {
            Append(item);
            return;
        }
        Node *current = head;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        Node *newNode = new Node(item);
        newNode->next = current->next;
        current->next = newNode;
        ++size;
    }

    LinkedList<T> *Concat(const LinkedList<T> *list) const
    {
        auto result = new LinkedList<T>(*this);
        Node *current = list->head;
        while (current)
        {
            result->Append(current->data);
            current = current->next;
        }
        return result;
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
            throw std::out_of_range("Invalid indices");
        auto result = new LinkedList<T>();
        Node *current = head;
        for (int i = 0; i < startIndex; ++i)
        {
            current = current->next;
        }
        for (int i = startIndex; i <= endIndex; ++i)
        {
            result->Append(current->data);
            current = current->next;
        }
        return result;
    }

   
    std::vector<T> ToArray() const
    {
        std::vector<T> result;
        result.reserve(size);
        Node *current = head;
        while (current)
        {
            result.push_back(current->data);
            current = current->next;
        }
        return result;
    }


    T &operator[](int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        Node *current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");
        Node *current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    void RemoveAt(int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of range");

        if (index == 0)
        {
            Node *toDelete = head;
            head = head->next;
            if (head == nullptr) 
                tail = nullptr;
            delete toDelete;
        }
        else
        {
            Node *prev = head;
            for (int i = 0; i < index - 1; ++i)
            {
                prev = prev->next;
            }
            Node *toDelete = prev->next;
            prev->next = toDelete->next;
            if (toDelete == tail) 
                tail = prev;
            delete toDelete;
        }
        --size;
    }
};
