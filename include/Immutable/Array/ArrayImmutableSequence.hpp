#pragma once

#include "include/Immutable/ImmutableSequence.hpp"
#include "include/core/DynamicArray.hpp"
#include <vector>
#include <memory>
#include <functional>
#include <utility>
#include <stdexcept>

template <typename T>
class ArrayImmutableSequence : public ImmutableSequence<T>
{
private:
    DynamicArray<T> data;

public:
    ArrayImmutableSequence(const T *items, int count)
        : data(items, count)
    {
    }

    ArrayImmutableSequence(const std::vector<T> &items)
        : data(items.data(), items.size())
    {
    }

    T GetFirst() const override
    {
        if (data.GetSize() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.Get(0);
    }

    T GetLast() const override
    {
        if (data.GetSize() == 0)
            throw std::out_of_range("Sequence is empty");
        return data.Get(data.GetSize() - 1);
    }

    T Get(int index) const override
    {
        return data.Get(index);
    }

    int GetLength() const override
    {
        return data.GetSize();
    }

    std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        auto subVec = data.GetSubVector(startIndex, endIndex);
        return std::make_unique<ArrayImmutableSequence<T>>(subVec);
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        auto vec = data.ToVector();
        vec.push_back(item);
        return std::make_unique<ArrayImmutableSequence<T>>(vec);
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        auto vec = data.ToVector();
        vec.insert(vec.begin(), item);
        return std::make_unique<ArrayImmutableSequence<T>>(vec);
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        auto vec = data.ToVector();
        if (index < 0 || index > static_cast<int>(vec.size()))
            throw std::out_of_range("Index out of bounds");
        vec.insert(vec.begin() + index, item);
        return std::make_unique<ArrayImmutableSequence<T>>(vec);
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        auto vec = data.ToVector();
        for (int i = 0; i < list->GetLength(); ++i)
        {
            vec.push_back(list->Get(i));
        }
        return std::make_unique<ArrayImmutableSequence<T>>(vec);
    }

    std::unique_ptr<ArrayImmutableSequence<T>> Map(std::function<T(const T &)> func) const
    {
        std::vector<T> mapped;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            mapped.push_back(func(data.Get(i)));
        }
        return std::make_unique<ArrayImmutableSequence<T>>(mapped);
    }

    std::unique_ptr<ArrayImmutableSequence<T>> MapIndexed(std::function<T(const T &, int)> func) const
    {
        std::vector<T> mapped;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            mapped.push_back(func(data.Get(i), i));
        }
        return std::make_unique<ArrayImmutableSequence<T>>(mapped);
    }

    T Reduce(std::function<T(const T &, const T &)> func, T initial) const
    {
        T accumulator = initial;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            accumulator = func(accumulator, data.Get(i));
        }
        return accumulator;
    }

    std::unique_ptr<ArrayImmutableSequence<T>> Where(std::function<bool(const T &)> predicate) const
    {
        std::vector<T> filtered;
        for (int i = 0; i < data.GetSize(); ++i)
        {
            if (predicate(data.Get(i)))
                filtered.push_back(data.Get(i));
        }
        return std::make_unique<ArrayImmutableSequence<T>>(filtered);
    }

    template <typename U>
    std::unique_ptr<ArrayImmutableSequence<std::pair<T, U>>> Zip(const ISequence<U> *other) const
    {
        int minLength = std::min(data.GetSize(), other->GetLength());
        std::vector<std::pair<T, U>> zipped;
        for (int i = 0; i < minLength; ++i)
        {
            zipped.emplace_back(data.Get(i), other->Get(i));
        }
        return std::make_unique<ArrayImmutableSequence<std::pair<T, U>>>(zipped);
    }
};
