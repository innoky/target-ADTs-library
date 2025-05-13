#pragma once
#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include <stdexcept>

template <typename T>
class PriorityQueue
{
private:
    MutableSequence<T> *seq;

    void BubbleUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (seq->Get(parent) < seq->Get(index))
            {
                std::swap((*seq)[parent], (*seq)[index]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void BubbleDown(int index)
    {
        int size = seq->GetLength();
        while (true)
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && seq->Get(left) > seq->Get(largest))
                largest = left;
            if (right < size && seq->Get(right) > seq->Get(largest))
                largest = right;

            if (largest != index)
            {
                std::swap((*seq)[index], (*seq)[largest]);
                index = largest;
            }
            else
            {
                break;
            }
        }
    }

public:
    PriorityQueue()
    {
        seq = new ArrayMutableSequence<T>();
    }
    ~PriorityQueue()
    {
        delete seq;
    }

    void Enqueue(const T &item)
    {
        seq->AppendInPlace(item);
        BubbleUp(seq->GetLength() - 1);
    }

    void Enqueue(T &&item)
    {
        seq->AppendInPlace(std::move(item));
        BubbleUp(seq->GetLength() - 1);
    }

    T Dequeue()
    {
        if (seq->GetLength() == 0)
        {
            throw std::out_of_range("PriorityQueue is empty");
        }

        T top = seq->GetFirst(); 

        (*seq)[0] = seq->Get(seq->GetLength() - 1);
        seq->RemoveAtInPlace(seq->GetLength() - 1);

        if (!IsEmpty())
        {
            BubbleDown(0);
        }

        return top;
    }

    T Peek() const
    {
        if (seq->GetLength() == 0)
        {
            throw std::out_of_range("PriorityQueue is empty");
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
