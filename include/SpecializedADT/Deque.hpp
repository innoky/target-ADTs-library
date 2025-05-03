#pragma once
#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include <stdexcept>

template <typename T>
class Deque
{
private:
    MutableSequence<T> *seq;

public:
    Deque()
    {
        seq = new ArrayMutableSequence<T>();
    }
    ~Deque()
    {
        delete seq;
    }

    void PushFront(const T &item)
    {
        seq->PrependInPlace(item);
    }

    void PushBack(const T &item)
    {
        seq->AppendInPlace(item);
    }

    T PopFront()
    {
        if (seq->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        T first = seq->GetFirst();
        seq->RemoveAtInPlace(0);
        return first;
    }

    T PopBack()
    {
        if (seq->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        int lastIndex = seq->GetLength() - 1;
        T last = seq->GetLast();
        seq->RemoveAtInPlace(lastIndex);
        return last;
    }

    T PeekFront() const
    {
        if (seq->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        return seq->GetFirst();
    }

    T PeekBack() const
    {
        if (seq->GetLength() == 0)
            throw std::out_of_range("Deque is empty");
        return seq->GetLast();
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
