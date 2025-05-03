#pragma once

#include <memory>

template <typename T>
class ISequence
{
public:
    virtual ~ISequence() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    virtual std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual std::unique_ptr<ISequence<T>> Append(T item) = 0;
    virtual std::unique_ptr<ISequence<T>> Prepend(T item) = 0;
    virtual std::unique_ptr<ISequence<T>> InsertAt(T item, int index) = 0;
    virtual std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) = 0;
};
