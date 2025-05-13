#include <cassert>
#include <iostream>
#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include "include/Muttable/List/ListMutableSequence.hpp"
#include "include/Immutable/Array/ArrayImmutableSequence.hpp"
#include "include/Immutable/List/ListImmutableSequence.hpp"
#include "include/SpecializedADT/SegmentedDeque.hpp"

#include "include/SpecializedADT/Queue.hpp"
#include "include/SpecializedADT/Deque.hpp"

void TestArrayMutableSequence()
{
    std::cout << "Testing ArrayMutableSequence..." << std::endl;
    int items[] = {1, 2, 3, 4, 5};
    ArrayMutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    seq.AppendInPlace(6);
    assert(seq.GetLast() == 6);
    assert(seq.GetLength() == 6);

    seq.PrependInPlace(0);
    assert(seq.GetFirst() == 0);
    assert(seq.GetLength() == 7);

    seq.InsertAtInPlace(99, 3);
    assert(seq.Get(3) == 99);
    assert(seq.GetLength() == 8);

    seq.RemoveAtInPlace(3);
    assert(seq.Get(3) != 99);
    assert(seq.GetLength() == 7);

    seq.RemoveAtInPlace(0);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLength() == 6);

    seq.RemoveAtInPlace(seq.GetLength() - 1);
    assert(seq.GetLast() == 5);
    assert(seq.GetLength() == 5);

    seq[3] = 55;
    assert(seq[3] == 55);

    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    ArrayMutableSequence<int> otherSeq(items, 5);
    seq.ConcatInPlace(&otherSeq);
    assert(seq.GetLength() == 10);
    assert(seq.GetLast() == 5);

    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    int count = 0;
    for (auto &val : seq)
    {
        (void)val; 
        count++;
    }
    assert(count == seq.GetLength());

    std::cout << "ArrayMutableSequence tests passed!" << std::endl;
}

void TestListMutableSequence()
{
    std::cout << "Testing ListMutableSequence..." << std::endl;
    int items[] = {1, 2, 3, 4, 5};
    ListMutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    seq.AppendInPlace(6);
    assert(seq.GetLast() == 6);
    assert(seq.GetLength() == 6);

    seq.PrependInPlace(0);
    assert(seq.GetFirst() == 0);
    assert(seq.GetLength() == 7);

    seq.InsertAtInPlace(99, 3);
    assert(seq.Get(3) == 99);
    assert(seq.GetLength() == 8);

    seq.RemoveAtInPlace(3);
    assert(seq.Get(3) != 99);
    assert(seq.GetLength() == 7);

    seq.RemoveAtInPlace(0);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLength() == 6);

    seq.RemoveAtInPlace(seq.GetLength() - 1);
    assert(seq.GetLast() == 5);
    assert(seq.GetLength() == 5);

    seq[3] = 55;
    assert(seq[3] == 55);

    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    ListMutableSequence<int> otherSeq(items, 5);
    seq.ConcatInPlace(&otherSeq);
    assert(seq.GetLength() == 10);
    assert(seq.GetLast() == 5);

    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    int count = 0;
    for (auto &val : seq)
    {
        (void)val;
        count++;
    }
    assert(count == seq.GetLength());

    std::cout << "ListMutableSequence tests passed!" << std::endl;
}

void TestArrayImmutableSequence()
{
    std::cout << "Testing ArrayImmutableSequence..." << std::endl;
    int items[] = {1, 2, 3, 4, 5};
    ArrayImmutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    auto appended = seq.Append(6);
    assert(appended->GetLast() == 6);
    assert(appended->GetLength() == 6);

    auto prepended = seq.Prepend(0);
    assert(prepended->GetFirst() == 0);
    assert(prepended->GetLength() == 6);

    auto inserted = seq.InsertAt(99, 3);
    assert(inserted->Get(3) == 99);
    assert(inserted->GetLength() == 6);

    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    ArrayImmutableSequence<int> otherSeq(items, 5);
    auto concatenated = seq.Concat(&otherSeq);
    assert(concatenated->GetLength() == 10);
    assert(concatenated->GetLast() == 5);

    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    std::cout << "ArrayImmutableSequence tests passed!" << std::endl;
}

void TestListImmutableSequence()
{
    std::cout << "Testing ListImmutableSequence..." << std::endl;
    int items[] = {1, 2, 3, 4, 5};
    ListImmutableSequence<int> seq(items, 5);

    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    auto appended = seq.Append(6);
    assert(appended->GetLast() == 6);
    assert(appended->GetLength() == 6);

    auto prepended = seq.Prepend(0);
    assert(prepended->GetFirst() == 0);
    assert(prepended->GetLength() == 6);

    auto inserted = seq.InsertAt(99, 3);
    assert(inserted->Get(3) == 99);
    assert(inserted->GetLength() == 6);

    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    ListImmutableSequence<int> otherSeq(items, 5);
    auto concatenated = seq.Concat(&otherSeq);
    assert(concatenated->GetLength() == 10);
    assert(concatenated->GetLast() == 5);

    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    std::cout << "ListImmutableSequence tests passed!" << std::endl;
}

void TestQueue()
{
    std::cout << "Testing Queue..." << std::endl;
    Queue<int> queue;

    assert(queue.IsEmpty());
    try
    {
        queue.Dequeue();
        assert(false); 
    }
    catch (const std::out_of_range &)
    {
    }

    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    assert(!queue.IsEmpty());
    assert(queue.GetLength() == 3);

    assert(queue.Peek() == 10);
    assert(queue.Dequeue() == 10);
    assert(queue.Dequeue() == 20);
    assert(queue.Dequeue() == 30);

    assert(queue.IsEmpty());

    queue.Enqueue(40);
    assert(queue.Peek() == 40);
    assert(queue.Dequeue() == 40);

    std::cout << "Queue tests passed!" << std::endl;
}

void TestDeque()
{
    std::cout << "Testing Deque..." << std::endl;
    Deque<int> deque;

    assert(deque.IsEmpty());
    try
    {
        deque.PopFront();
        assert(false); 
    }
    catch (const std::out_of_range &)
    {
    }
    try
    {
        deque.PopBack();
        assert(false); 
    }
    catch (const std::out_of_range &)
    {
    }

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);
    assert(deque.GetLength() == 3);
    assert(deque.PeekFront() == 1);
    assert(deque.PeekBack() == 3);

    assert(deque.PopFront() == 1);
    assert(deque.PopFront() == 2);
    assert(deque.PopFront() == 3);
    assert(deque.IsEmpty());

    deque.PushFront(10);
    deque.PushFront(20);
    deque.PushFront(30);
    assert(deque.GetLength() == 3);
    assert(deque.PeekFront() == 30);
    assert(deque.PeekBack() == 10);

    assert(deque.PopBack() == 10);
    assert(deque.PopBack() == 20);
    assert(deque.PopBack() == 30);
    assert(deque.IsEmpty());

    deque.PushBack(100);
    deque.PushFront(200);
    deque.PushBack(300);
    assert(deque.GetLength() == 3);
    assert(deque.PeekFront() == 200);
    assert(deque.PeekBack() == 300);

    assert(deque.PopFront() == 200);
    assert(deque.PopBack() == 300);
    assert(deque.PopFront() == 100);
    assert(deque.IsEmpty());

    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);
    deque.PushFront(0);
    deque.PushFront(-1);
    assert(deque.GetLength() == 5);
    assert(deque.PeekFront() == -1);
    assert(deque.PeekBack() == 3);

    assert(deque.PopFront() == -1);
    assert(deque.PopFront() == 0);
    assert(deque.PopFront() == 1);
    assert(deque.PopFront() == 2);
    assert(deque.PopFront() == 3);
    assert(deque.IsEmpty());

    std::cout << "Deque tests passed!" << std::endl;
}

void TestSegmentedDeque()
{
    std::cout << "Testing SegmentedDeque..." << std::endl;

    SegmentedDeque<std::string> deque;

    assert(deque.GetLength() == 0);

    deque.AppendInPlace("A");
    deque.AppendInPlace("B");
    deque.AppendInPlace("C");

    assert(deque.GetLength() == 3);
    assert(deque.GetFirst() == "A");
    assert(deque.GetLast() == "C");
    assert(deque.Get(1) == "B");

    deque.PrependInPlace("Z");
    assert(deque.GetLength() == 4);
    assert(deque.GetFirst() == "Z");

    deque.InsertAtInPlace("X", 2);
    assert(deque.Get(2) == "X");
    assert(deque.GetLength() == 5);

    deque.RemoveAtInPlace(2); 
    assert(deque.Get(2) != "X");
    assert(deque.GetLength() == 4);

    SegmentedDeque<std::string> other;
    other.AppendInPlace("D");
    other.AppendInPlace("E");

    deque.ConcatInPlace(&other);
    assert(deque.GetLength() == 6);
    assert(deque.GetLast() == "E");

    deque[3] = "Q";
    assert(deque[3] == "Q");

    std::cout << "SegmentedDeque tests passed!" << std::endl;
}

int main()
{
    TestArrayMutableSequence();
    TestListMutableSequence();
    TestArrayImmutableSequence();
    TestListImmutableSequence();
    TestQueue();
    TestDeque();
    TestSegmentedDeque();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}