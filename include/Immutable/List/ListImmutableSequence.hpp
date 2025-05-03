#pragma once

#include "include/Immutable/ImmutableSequence.hpp"
#include "include/core/LinkedList.hpp"
#include <memory>
#include <stdexcept>

template <typename T>
class ListImmutableSequence : public ImmutableSequence<T>
{
private:
    LinkedList<T> data;

public:
    ListImmutableSequence() = default;

    ListImmutableSequence(const T *items, int count) : data(items, count) {}

    ListImmutableSequence(const std::vector<T> &items)
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
        return std::make_unique<ListImmutableSequence<T>>(array);
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        auto arrayCopy = data.ToArray();
        arrayCopy.push_back(item);
        return std::make_unique<ListImmutableSequence<T>>(arrayCopy);
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        auto arrayCopy = data.ToArray();
        arrayCopy.insert(arrayCopy.begin(), item);
        return std::make_unique<ListImmutableSequence<T>>(arrayCopy);
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        if (index < 0 || index > GetLength())
            throw std::out_of_range("Invalid index for insert");
        auto arrayCopy = data.ToArray();
        arrayCopy.insert(arrayCopy.begin() + index, item);
        return std::make_unique<ListImmutableSequence<T>>(arrayCopy);
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        auto arrayCopy = data.ToArray();
        for (int i = 0; i < list->GetLength(); ++i)
        {
            arrayCopy.push_back(list->Get(i));
        }
        return std::make_unique<ListImmutableSequence<T>>(arrayCopy);
    }
   
    std::unique_ptr<ListImmutableSequence<T>> Map(std::function<T(const T &)> func) const
    {
       
        std::vector<T> mappedItems;
        for (int i = 0; i < data.GetLength(); ++i)
        {
            mappedItems.push_back(func(data.Get(i)));
        }
        return std::make_unique<ListImmutableSequence<T>>(mappedItems.data(), mappedItems.size());
    }
  
    T Reduce(std::function<T(const T &, const T &)> func, T initial) const
    {
        T accumulator = initial;
        for (int i = 0; i < data.GetLength(); ++i)
        {
            accumulator = func(accumulator, data.Get(i));
        }
        return accumulator;
    }

    std::unique_ptr<ListImmutableSequence<T>> Where(std::function<bool(const T &)> predicate) const
    {
        std::vector<T> filteredItems;
        for (int i = 0; i < data.GetLength(); ++i)
        {
            if (predicate(data.Get(i)))
            {
                filteredItems.push_back(data.Get(i));
            }
        }
        return std::make_unique<ListImmutableSequence<T>>(filteredItems.data(), filteredItems.size());
    }

    template <typename U>
    std::unique_ptr<ListImmutableSequence<std::pair<T, U>>> Zip(const ISequence<U> *other) const
    {
        int minLength = std::min(this->GetLength(), other->GetLength());
        std::vector<std::pair<T, U>> zippedItems;
        for (int i = 0; i < minLength; ++i)
        {
            zippedItems.emplace_back(data.Get(i), other->Get(i));
        }
        return std::make_unique<ListImmutableSequence<std::pair<T, U>>>(zippedItems.data(), zippedItems.size());
    }
};
