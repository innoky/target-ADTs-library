#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include <memory>
#include <optional>

template <typename T>
class BufferedStream : public MutableSequence<T>
{
private:
    std::unique_ptr<MutableSequence<T>> buffer;
    std::optional<T> current;

public:
    BufferedStream(){
        buffer = std::make_unique<ArrayMutableSequence<T>>();
    }

    void SetCurrent(const T &item)
    {
        current = item;
    }

    const std::optional<T> &GetCurrent() const
    {
        return current;
    }

    void CommitCurrentToBuffer()
    {
        if (current.has_value())
        {
            buffer->AppendInPlace(current.value());
            current.reset();
        }
    }

    void Add(const T& item)
    {
        buffer->AppendInPlace(item);
    }

    T GetFirst() const override { return buffer->GetFirst(); }
    T GetLast() const override { return buffer->GetLast(); }
    T Get(int index) const override { return buffer->Get(index); }
    int GetLength() const override { return buffer->GetLength(); }

    std::unique_ptr<ISequence<T>> GetSubsequence(int startIndex, int endIndex) const override
    {
        return buffer->GetSubsequence(startIndex, endIndex);
    }

    std::unique_ptr<ISequence<T>> Append(T item) override
    {
        return buffer->Append(item);
    }

    std::unique_ptr<ISequence<T>> Prepend(T item) override
    {
        return buffer->Prepend(item);
    }

    std::unique_ptr<ISequence<T>> InsertAt(T item, int index) override
    {
        return buffer->InsertAt(item, index);
    }

    std::unique_ptr<ISequence<T>> Concat(const ISequence<T> *list) override
    {
        return buffer->Concat(list);
    }

    void AppendInPlace(T item) override
    {
        buffer->AppendInPlace(item);
    }

    void PrependInPlace(T item) override
    {
        buffer->PrependInPlace(item);
    }

    void InsertAtInPlace(T item, int index) override
    {
        buffer->InsertAtInPlace(item, index);
    }

    void RemoveAtInPlace(int index) override
    {
        buffer->RemoveAtInPlace(index);
    }

    void ConcatInPlace(const ISequence<T> *list) override
    {
        buffer->ConcatInPlace(list);
    }
};