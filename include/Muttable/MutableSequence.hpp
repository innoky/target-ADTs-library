#pragma once

#include "include/ISequence.hpp"

template <typename T>
class MutableSequence : public ISequence<T>
{
public:
    virtual ~MutableSequence() = default;

    virtual T GetFirst() const override = 0;
    virtual T GetLast() const override = 0;
    virtual T Get(int index) const override = 0;
    virtual int GetLength() const override = 0;
    
    virtual std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override = 0;

    virtual std::unique_ptr<ISequence<T>> Append(T item) override = 0;
    virtual std::unique_ptr<ISequence<T>> Prepend(T item) override = 0;
    virtual std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override = 0;
    virtual std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override = 0;

   
    virtual void AppendInPlace(T item) = 0;
    virtual void PrependInPlace(T item) = 0;
    virtual void InsertAtInPlace(T item, int index) = 0;
    virtual void ConcatInPlace(const ISequence<T> *list) = 0;
    virtual void RemoveAtInPlace(int index) = 0;
};
