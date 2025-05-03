#pragma once

#include <memory>
#include <utility>
#include "Muttable/Array/ArrayMutableSequence.hpp"
#include "Muttable/List/ListMutableSequence.hpp"

template <typename SequenceT, typename Enable = void>
struct SequenceUnzipHelper
{
    static void Unzip(const SequenceT &)
    {
        static_assert(sizeof(SequenceT) == -1,
                      "Unzip is only available for sequences of std::pair");
    }
};


template <typename A, typename B>
struct SequenceUnzipHelper<ArrayMutableSequence<std::pair<A, B>>>
{
    static std::pair<
        std::unique_ptr<ArrayMutableSequence<A>>,
        std::unique_ptr<ArrayMutableSequence<B>>>
    Unzip(const ArrayMutableSequence<std::pair<A, B>> &seq)
    {
        auto firstSeq = std::make_unique<ArrayMutableSequence<A>>();
        auto secondSeq = std::make_unique<ArrayMutableSequence<B>>();

        for (const auto &item : seq)
        {
            firstSeq->AppendInPlace(item.first);
            secondSeq->AppendInPlace(item.second);
        }
        return {std::move(firstSeq), std::move(secondSeq)};
    }
};

template <typename A, typename B>
struct SequenceUnzipHelper<ListMutableSequence<std::pair<A, B>>>
{
    static std::pair<
        std::unique_ptr<ListMutableSequence<A>>,
        std::unique_ptr<ListMutableSequence<B>>>
    Unzip(const ListMutableSequence<std::pair<A, B>> &seq)
    {
        auto firstSeq = std::make_unique<ListMutableSequence<A>>();
        auto secondSeq = std::make_unique<ListMutableSequence<B>>();

        for (const auto &item : seq)
        {
            firstSeq->AppendInPlace(item.first);
            secondSeq->AppendInPlace(item.second);
        }
        return {std::move(firstSeq), std::move(secondSeq)};
    }
};

template <typename Seq>
auto UnzipSequence(const Seq &seq)
{
    return SequenceUnzipHelper<Seq>::Unzip(seq);
}
