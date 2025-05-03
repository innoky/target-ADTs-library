#pragma once
#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include <stdexcept>

template <typename T>
class Queue
{
private:
    MutableSequence<T> *seq;

public:
    Queue()
    {
        seq = new ArrayMutableSequence<T>();
    }
    ~Queue()
    {
        delete seq;
    }
    void Enqueue(const T &item)
    {
        seq->AppendInPlace(item);
    }
    void Enqueue(T &&item)
    {
        seq->AppendInPlace(std::move(item));
    }
    T Dequeue()
    {
        if (seq->GetLength() == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        T first = seq->GetFirst();
        seq->RemoveAtInPlace(0);
        return first;
    }
    T Peek() const
    {
        if (seq->GetLength() == 0)
        {
            throw std::out_of_range("Queue is empty");
        }
        return seq->GetFirst();
    }
    int GetLength() const
    {
        return seq->GetLength();
    }
    bool IsEmpty() const
    {
        return seq->GetLength() == 0;
    }
};
