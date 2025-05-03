#pragma once

#include <memory>
#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include "include/Muttable/List/ListMutableSequence.hpp"
#include "include/Immutable/Array/ArrayImmutableSequence.hpp"
#include "include/Immutable/List/ListImmutableSequence.hpp"

class SequenceUI
{
public:
    void Run();

private:
    template <typename SeqType>
    void HandleMutableSequence();

    template <typename SeqType>
    void HandleImmutableSequence();

    void PrintMenu();
};
