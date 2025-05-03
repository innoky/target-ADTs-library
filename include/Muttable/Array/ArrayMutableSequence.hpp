#pragma once

#include "include/Muttable/MutableSequence.hpp"
#include "include/core/DynamicArray.hpp"
#include <memory>
#include <stdexcept>
#include <functional>
#include <vector>


template<class>
struct always_false : std::false_type {};


template <typename T>
class ArrayMutableSequenceIterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    ArrayMutableSequenceIterator(T *ptr) : ptr_(ptr) {}

    T &operator*() const { return *ptr_; }
    T *operator->() { return ptr_; }
    ArrayMutableSequenceIterator &operator++()
    {
        ptr_++;
        return *this;
    }
    ArrayMutableSequenceIterator operator++(int)
    {
        ArrayMutableSequenceIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    bool operator==(const ArrayMutableSequenceIterator &other) const
    {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const ArrayMutableSequenceIterator &other) const
    {
        return ptr_ != other.ptr_;
    }

private:
    T *ptr_;
};

template <typename T>
class ArrayMutableSequence : public MutableSequence<T>
{
private:
    DynamicArray<T> data;

public:
    ArrayMutableSequence() : data(0) {}
    ArrayMutableSequence(const T *items, int count) : data(items, count) {}

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
        if (startIndex < 0 || endIndex >= GetLength() || startIndex > endIndex)
            throw std::out_of_range("Invalid indices for subsequence");
        int newSize = endIndex - startIndex + 1;
        std::vector<T> subItems;
        for (int i = startIndex; i <= endIndex; ++i)
        {
            subItems.push_back(data.Get(i));
        }
        return std::make_unique<ArrayMutableSequence<T>>(subItems.data(), newSize);
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        auto newSeq = std::make_unique<ArrayMutableSequence<T>>(data.GetRawData(), data.GetSize());
        newSeq->AppendInPlace(item);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        auto newSeq = std::make_unique<ArrayMutableSequence<T>>(data.GetRawData(), data.GetSize());
        newSeq->PrependInPlace(item);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        auto newSeq = std::make_unique<ArrayMutableSequence<T>>(data.GetRawData(), data.GetSize());
        newSeq->InsertAtInPlace(item, index);
        return newSeq;
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        auto newSeq = std::make_unique<ArrayMutableSequence<T>>(data.GetRawData(), data.GetSize());
        newSeq->ConcatInPlace(list);
        return newSeq;
    }

   
    void AppendInPlace(T item) override
    {
        data.Resize(data.GetSize() + 1);
        data.Set(data.GetSize() - 1, item);
    }

    void PrependInPlace(T item) override
    {
        data.Resize(data.GetSize() + 1);
        for (int i = data.GetSize() - 1; i > 0; --i)
        {
            data.Set(i, data.Get(i - 1));
        }
        data.Set(0, item);
    }

    void InsertAtInPlace(T item, int index) override
    {
        if (index < 0 || index > data.GetSize())
            throw std::out_of_range("Invalid index");
        data.Resize(data.GetSize() + 1);
        for (int i = data.GetSize() - 1; i > index; --i)
        {
            data.Set(i, data.Get(i - 1));
        }
        data.Set(index, item);
    }

    void ConcatInPlace(const ISequence<T> *list) override
    {
        int oldSize = data.GetSize();
        int listSize = list->GetLength();
        data.Resize(oldSize + listSize);
        for (int i = 0; i < listSize; ++i)
        {
            data.Set(oldSize + i, list->Get(i));
        }
    }

    
    ArrayMutableSequenceIterator<T> begin()
    {
        return ArrayMutableSequenceIterator<T>(data.GetRawData());
    }

    ArrayMutableSequenceIterator<T> end()
    {
        return ArrayMutableSequenceIterator<T>(data.GetRawData() + data.GetSize());
    }

    
    T &operator[](int index)
    {
        if (index < 0 || index >= data.GetSize())
            throw std::out_of_range("Invalid index");
        return data[index]; 
    }

   
    std::unique_ptr<ArrayMutableSequence<T>> Map(std::function<T(const T &)> func) const
    {
        auto result = std::make_unique<ArrayMutableSequence<T>>();
        for (int i = 0; i < GetLength(); ++i)
        {
            result->AppendInPlace(func(data.Get(i)));
        }
        return result;
    }


    std::unique_ptr<ArrayMutableSequence<T>> MapIndexed(std::function<T(const T &, int)> func) const
    {
        auto result = std::make_unique<ArrayMutableSequence<T>>();
        for (int i = 0; i < GetLength(); ++i)
        {
            result->AppendInPlace(func(data.Get(i), i));
        }
        return result;
    }


    T Reduce(std::function<T(const T &, const T &)> func, T initial) const
    {
        T accumulator = initial;
        for (int i = 0; i < GetLength(); ++i)
        {
            accumulator = func(accumulator, data.Get(i));
        }
        return accumulator;
    }


    std::unique_ptr<ArrayMutableSequence<T>> Where(std::function<bool(const T &)> predicate) const
    {
        auto result = std::make_unique<ArrayMutableSequence<T>>();
        for (int i = 0; i < GetLength(); ++i)
        {
            if (predicate(data.Get(i)))
            {
                result->AppendInPlace(data.Get(i));
            }
        }
        return result;
    }

   
    template <typename U>
    std::unique_ptr<ArrayMutableSequence<std::pair<T, U>>> Zip(const ISequence<U> *other) const
    {
        int minLength = std::min(GetLength(), other->GetLength());
        auto result = std::make_unique<ArrayMutableSequence<std::pair<T, U>>>();
        for (int i = 0; i < minLength; ++i)
        {
            result->AppendInPlace({data.Get(i), other->Get(i)});
        }
        return result;
    }

    void RemoveAtInPlace(int index) override
    {
        if (index < 0 || index >= data.GetSize())
            throw std::out_of_range("Invalid index");
        for (int i = index; i < data.GetSize() - 1; ++i)
        {
            data.Set(i, data.Get(i + 1));
        }
        data.Resize(data.GetSize() - 1);
    }
};
