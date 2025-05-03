#pragma once

#include "include/Muttable/MutableSequence.hpp"
#include "include/core/LinkedList.hpp" 
#include <memory>
#include <stdexcept>
#include <functional>
#include <utility>

template <typename T>
class ListMutableSequenceIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit ListMutableSequenceIterator(typename LinkedList<T>::Node *node) : current(node) {}

    T &operator*() const { return current->data; }
    T *operator->() { return &(current->data); }

    ListMutableSequenceIterator &operator++()
    {
        if (current)
            current = current->next;
        return *this;
    }

    ListMutableSequenceIterator operator++(int)
    {
        ListMutableSequenceIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const ListMutableSequenceIterator &other) const
    {
        return current == other.current;
    }

    bool operator!=(const ListMutableSequenceIterator &other) const
    {
        return current != other.current;
    }

private:
    typename LinkedList<T>::Node *current;
};

template <typename T>
class ListMutableSequence : public MutableSequence<T>
{
private:
    LinkedList<T> data;

public:
    ListMutableSequence() = default;
    ListMutableSequence(const T *items, int count) : data(items, count) {}
    ListMutableSequence(const std::vector<T> &items) : ListMutableSequence()
    {
        for (const auto &item : items)
        {
            data.Append(item);
        }
    }

    T GetFirst() const override
    {
        if (data.GetLength() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.GetFirst();
    }

    T GetLast() const override
    {
        if (data.GetLength() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.GetLast();
    }

    T Get(int index) const override
    {
        return data.Get(index);
    }

    int GetLength() const override
    {
        return data.GetLength();
    }

    std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
            throw std::out_of_range("Invalid indices for subsequence");
        auto subList = data.GetSubList(startIndex, endIndex);
        auto array = subList->ToArray();
        return std::make_unique<ListMutableSequence<T>>(array);
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        auto newSeq = std::make_unique<ListMutableSequence<T>>(data.ToArray());
        newSeq->AppendInPlace(item);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        auto newSeq = std::make_unique<ListMutableSequence<T>>(data.ToArray());
        newSeq->PrependInPlace(item);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        auto newSeq = std::make_unique<ListMutableSequence<T>>(data.ToArray());
        newSeq->InsertAtInPlace(item, index);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        auto newSeq = std::make_unique<ListMutableSequence<T>>(data.ToArray());
        newSeq->ConcatInPlace(list);
        return newSeq;
    }

    // In-place методы
    void AppendInPlace(T item) override
    {
        data.Append(item);
    }

    void PrependInPlace(T item) override
    {
        data.Prepend(item);
    }

    void InsertAtInPlace(T item, int index) override
    {
        data.InsertAt(item, index);
    }

    void ConcatInPlace(const ISequence<T> *list) override
    {
        for (int i = 0; i < list->GetLength(); ++i)
        {
            data.Append(list->Get(i));
        }
    }

    ListMutableSequenceIterator<T> begin() const
    {
        return ListMutableSequenceIterator<T>(data.GetHead());
    }

    ListMutableSequenceIterator<T> end() const
    {
        return ListMutableSequenceIterator<T>(nullptr);
    }

    T &operator[](int index)
    {
        return data[index];
    }

    const T &operator[](int index) const
    {
        return data[index];
    }

    std::unique_ptr<ListMutableSequence<T>> Map(std::function<T(const T &)> func) const
    {
        auto result = std::make_unique<ListMutableSequence<T>>();
        for (auto &item : *this)
        {
            result->AppendInPlace(func(item));
        }
        return result;
    }

    std::unique_ptr<ListMutableSequence<T>> MapIndexed(std::function<T(const T &, int)> func) const
    {
        auto result = std::make_unique<ListMutableSequence<T>>();
        int index = 0;
        for (auto &item : *this)
        {
            result->AppendInPlace(func(item, index++));
        }
        return result;
    }

    T Reduce(std::function<T(const T &, const T &)> func, T initial) const
    {
        T accumulator = initial;
        for (auto &item : *this)
        {
            accumulator = func(accumulator, item);
        }
        return accumulator;
    }

    std::unique_ptr<ListMutableSequence<T>> Where(std::function<bool(const T &)> predicate) const
    {
        auto result = std::make_unique<ListMutableSequence<T>>();
        for (auto &item : *this)
        {
            if (predicate(item))
            {
                result->AppendInPlace(item);
            }
        }
        return result;
    }

    template <typename U>
    std::unique_ptr<ListMutableSequence<std::pair<T, U>>> Zip(const ISequence<U> *other) const
    {
        int minLength = std::min(GetLength(), other->GetLength());
        auto result = std::make_unique<ListMutableSequence<std::pair<T, U>>>();
        auto it = begin();
        for (int i = 0; i < minLength; ++i, ++it)
        {
            result->AppendInPlace({*it, other->Get(i)});
        }
        return result;
    }

    void RemoveAtInPlace(int index) override
    {
        data.RemoveAt(index);
    }
};
