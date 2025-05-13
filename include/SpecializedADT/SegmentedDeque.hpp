#pragma once
#include "include/ISequence.hpp"
#include "include/Muttable/MutableSequence.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

template <typename T>
class SegmentedDeque : public MutableSequence<T>
{
private:
    static constexpr int SEGMENT_SIZE = 64;

    std::vector<std::unique_ptr<T[]>> segments;
    int totalLength = 0;

    int headIndex = SEGMENT_SIZE / 2;
    int tailIndex = SEGMENT_SIZE / 2;

    int bufferOffset = 0; 

    void ensureSegmentFront()
    {
        if (headIndex == 0)
        {
            segments.insert(segments.begin(), std::make_unique<T[]>(SEGMENT_SIZE));
            headIndex = SEGMENT_SIZE;
            bufferOffset++;
        }
    }

    void ensureSegmentBack()
    {
        if (tailIndex == segments.size() * SEGMENT_SIZE)
        {
            segments.push_back(std::make_unique<T[]>(SEGMENT_SIZE));
        }
    }

    std::pair<int, int> resolveIndex(int index) const
    {
        int logicalIndex = headIndex + index;
        int segmentIndex = logicalIndex / SEGMENT_SIZE;
        int withinSegment = logicalIndex % SEGMENT_SIZE;
        return {segmentIndex, withinSegment};
    }

public:
    SegmentedDeque()
    {
        segments.push_back(std::make_unique<T[]>(SEGMENT_SIZE));
    }

    SegmentedDeque(const SegmentedDeque &other)
    {
        totalLength = other.totalLength;
        headIndex = other.headIndex;
        tailIndex = other.tailIndex;

        segments.clear();
        for (const auto &seg : other.segments)
        {
            auto newSeg = std::make_unique<T[]>(SEGMENT_SIZE);
            for (int i = 0; i < SEGMENT_SIZE; ++i)
            {
                newSeg[i] = seg[i];
            }
            segments.push_back(std::move(newSeg));
        }
    }

    T GetFirst() const override { return Get(0); }

    T GetLast() const override { return Get(totalLength - 1); }

    T Get(int index) const override
    {
        if (index < 0 || index >= totalLength)
            throw std::out_of_range("Index out of range");
        auto [seg, offset] = resolveIndex(index);
        return segments[seg][offset];
    }

    int GetLength() const override { return totalLength; }

    std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        if (startIndex < 0 || endIndex >= totalLength || startIndex > endIndex)
            throw std::out_of_range("Invalid subsequence range");
        auto result = std::make_unique<SegmentedDeque<T>>();
        for (int i = startIndex; i <= endIndex; ++i)
            result->AppendInPlace(Get(i));
        return result;
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        auto copy = std::make_unique<SegmentedDeque<T>>(*this);
        copy->AppendInPlace(item);
        return copy;
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        auto copy = std::make_unique<SegmentedDeque<T>>(*this);
        copy->PrependInPlace(item);
        return copy;
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        auto copy = std::make_unique<SegmentedDeque<T>>(*this);
        copy->InsertAtInPlace(item, index);
        return copy;
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        auto copy = std::make_unique<SegmentedDeque<T>>(*this);
        copy->ConcatInPlace(list);
        return copy;
    }

    void AppendInPlace(T item) override
    {
        ensureSegmentBack();
        auto [seg, offset] = resolveIndex(totalLength);
        segments[seg][offset] = item;
        ++totalLength;
        ++tailIndex;
    }

    void PrependInPlace(T item) override
    {
        ensureSegmentFront();
        --headIndex;
        auto [seg, offset] = resolveIndex(0);
        segments[seg][offset] = item;
        ++totalLength;
    }

    void InsertAtInPlace(T item, int index) override
    {
        if (index == 0)
            return PrependInPlace(item);
        if (index == totalLength)
            return AppendInPlace(item);

        AppendInPlace(Get(totalLength - 1));
        for (int i = totalLength - 2; i > index; --i)
            (*this)[i] = Get(i - 1);
        (*this)[index] = item;
    }

    void ConcatInPlace(const ISequence<T> *list) override
    {
        for (int i = 0; i < list->GetLength(); ++i)
            AppendInPlace(list->Get(i));
    }

    void RemoveAtInPlace(int index) override
    {
        if (index < 0 || index >= totalLength)
            throw std::out_of_range("Index out of range");
        for (int i = index; i < totalLength - 1; ++i)
            (*this)[i] = Get(i + 1);
        --totalLength;
        --tailIndex;
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= totalLength)
            throw std::out_of_range("Index out of range");
        auto [seg, offset] = resolveIndex(index);
        return segments[seg][offset];
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= totalLength)
            throw std::out_of_range("Index out of range");
        auto [seg, offset] = resolveIndex(index);
        return segments[seg][offset];
    }
};
