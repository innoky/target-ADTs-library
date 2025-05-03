#include <cassert>
#include <iostream>
#include "include/Muttable/Array/ArrayMutableSequence.hpp"
#include "include/Muttable/List/ListMutableSequence.hpp"
#include "include/Immutable/Array/ArrayImmutableSequence.hpp"
#include "include/Immutable/List/ListImmutableSequence.hpp"

#include "include/SpecializedADT/Queue.hpp"
#include "include/SpecializedADT/Deque.hpp"

void TestArrayMutableSequence()
{
    std::cout << "Testing ArrayMutableSequence..." << std::endl;
    int items[] = {1, 2, 3, 4, 5};
    ArrayMutableSequence<int> seq(items, 5);

    // GetFirst / GetLast / Get
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    // AppendInPlace
    seq.AppendInPlace(6);
    assert(seq.GetLast() == 6);
    assert(seq.GetLength() == 6);

    // PrependInPlace
    seq.PrependInPlace(0);
    assert(seq.GetFirst() == 0);
    assert(seq.GetLength() == 7);

    // InsertAtInPlace
    seq.InsertAtInPlace(99, 3);
    assert(seq.Get(3) == 99);
    assert(seq.GetLength() == 8);

    // RemoveAtInPlace (удаляем 3-й элемент)
    seq.RemoveAtInPlace(3);
    assert(seq.Get(3) != 99);
    assert(seq.GetLength() == 7);

    // RemoveAtInPlace (удаляем первый элемент)
    seq.RemoveAtInPlace(0);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLength() == 6);

    // RemoveAtInPlace (удаляем последний элемент)
    seq.RemoveAtInPlace(seq.GetLength() - 1);
    assert(seq.GetLast() == 5);
    assert(seq.GetLength() == 5);

    // operator[]
    seq[3] = 55;
    assert(seq[3] == 55);

    // GetSubsequence
    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    // ConcatInPlace
    ArrayMutableSequence<int> otherSeq(items, 5);
    seq.ConcatInPlace(&otherSeq);
    assert(seq.GetLength() == 10);
    assert(seq.GetLast() == 5);

    // Map
    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    // Reduce
    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    // Where
    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    // Zip
    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    // Итерация
    int count = 0;
    for (auto &val : seq)
    {
        (void)val; // просто пробежка
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

    // GetFirst / GetLast / Get
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    // AppendInPlace
    seq.AppendInPlace(6);
    assert(seq.GetLast() == 6);
    assert(seq.GetLength() == 6);

    // PrependInPlace
    seq.PrependInPlace(0);
    assert(seq.GetFirst() == 0);
    assert(seq.GetLength() == 7);

    // InsertAtInPlace
    seq.InsertAtInPlace(99, 3);
    assert(seq.Get(3) == 99);
    assert(seq.GetLength() == 8);

    // RemoveAtInPlace (удаляем 3-й элемент)
    seq.RemoveAtInPlace(3);
    assert(seq.Get(3) != 99);
    assert(seq.GetLength() == 7);

    // RemoveAtInPlace (удаляем первый элемент)
    seq.RemoveAtInPlace(0);
    assert(seq.GetFirst() == 1);
    assert(seq.GetLength() == 6);

    // RemoveAtInPlace (удаляем последний элемент)
    seq.RemoveAtInPlace(seq.GetLength() - 1);
    assert(seq.GetLast() == 5);
    assert(seq.GetLength() == 5);

    // operator[]
    seq[3] = 55;
    assert(seq[3] == 55);

    // GetSubsequence
    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    // ConcatInPlace
    ListMutableSequence<int> otherSeq(items, 5);
    seq.ConcatInPlace(&otherSeq);
    assert(seq.GetLength() == 10);
    assert(seq.GetLast() == 5);

    // Map
    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    // Reduce
    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    // Where
    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    // Zip
    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    // Итерация
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

    // GetFirst / GetLast / Get
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    // Append
    auto appended = seq.Append(6);
    assert(appended->GetLast() == 6);
    assert(appended->GetLength() == 6);

    // Prepend
    auto prepended = seq.Prepend(0);
    assert(prepended->GetFirst() == 0);
    assert(prepended->GetLength() == 6);

    // InsertAt
    auto inserted = seq.InsertAt(99, 3);
    assert(inserted->Get(3) == 99);
    assert(inserted->GetLength() == 6);

    // GetSubsequence
    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    // Concat
    ArrayImmutableSequence<int> otherSeq(items, 5);
    auto concatenated = seq.Concat(&otherSeq);
    assert(concatenated->GetLength() == 10);
    assert(concatenated->GetLast() == 5);

    // Map
    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    // Reduce
    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    // Where
    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    // Zip
    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    std::cout << "ArrayImmutableSequence tests passed!" << std::endl;
}

void TestListImmutableSequence()
{
    std::cout << "Testing ListImmutableSequence..." << std::endl;
    int items[] = {1, 2, 3, 4, 5};
    ListImmutableSequence<int> seq(items, 5);

    // GetFirst / GetLast / Get
    assert(seq.GetFirst() == 1);
    assert(seq.GetLast() == 5);
    assert(seq.Get(2) == 3);

    // Append
    auto appended = seq.Append(6);
    assert(appended->GetLast() == 6);
    assert(appended->GetLength() == 6);

    // Prepend
    auto prepended = seq.Prepend(0);
    assert(prepended->GetFirst() == 0);
    assert(prepended->GetLength() == 6);

    // InsertAt
    auto inserted = seq.InsertAt(99, 3);
    assert(inserted->Get(3) == 99);
    assert(inserted->GetLength() == 6);

    // GetSubsequence
    auto subSeq = seq.GetSubsequence(2, 4);
    assert(subSeq->GetLength() == 3);
    assert(subSeq->Get(0) == seq.Get(2));

    // Concat
    ListImmutableSequence<int> otherSeq(items, 5);
    auto concatenated = seq.Concat(&otherSeq);
    assert(concatenated->GetLength() == 10);
    assert(concatenated->GetLast() == 5);

    // Map
    auto mapped = seq.Map([](const int &x)
                          { return x * 2; });
    assert(mapped->Get(0) == seq.Get(0) * 2);

    // Reduce
    int sum = seq.Reduce([](const int &acc, const int &x)
                         { return acc + x; }, 0);
    assert(sum > 0);

    // Where
    auto filtered = seq.Where([](const int &x)
                              { return x % 2 == 0; });
    for (int i = 0; i < filtered->GetLength(); ++i)
    {
        assert(filtered->Get(i) % 2 == 0);
    }

    // Zip
    auto zipped = seq.Zip(&otherSeq);
    assert(zipped->GetLength() == std::min(seq.GetLength(), otherSeq.GetLength()));

    std::cout << "ListImmutableSequence tests passed!" << std::endl;
}

void TestQueue()
{
    std::cout << "Testing Queue..." << std::endl;
    Queue<int> queue;

    // Проверка пустой очереди
    assert(queue.IsEmpty());
    try
    {
        queue.Dequeue();
        assert(false); // должно выбросить исключение
    }
    catch (const std::out_of_range &)
    {
    }

    // Enqueue / Dequeue
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

    // Дек пустой — проверяем исключения
    assert(deque.IsEmpty());
    try
    {
        deque.PopFront();
        assert(false); // должно выбросить
    }
    catch (const std::out_of_range &)
    {
    }
    try
    {
        deque.PopBack();
        assert(false); // должно выбросить
    }
    catch (const std::out_of_range &)
    {
    }

    // PushBack + PopFront (имитируем очередь)
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

    // PushFront + PopBack (имитируем стек)
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

    // Комбинированные операции
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

    // Проверим последовательность операций
    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushBack(3);
    deque.PushFront(0);
    deque.PushFront(-1);
    assert(deque.GetLength() == 5);
    assert(deque.PeekFront() == -1);
    assert(deque.PeekBack() == 3);

    // Полностью опустошаем
    assert(deque.PopFront() == -1);
    assert(deque.PopFront() == 0);
    assert(deque.PopFront() == 1);
    assert(deque.PopFront() == 2);
    assert(deque.PopFront() == 3);
    assert(deque.IsEmpty());

    std::cout << "Deque tests passed!" << std::endl;
}

int main()
{
    TestArrayMutableSequence();
    TestListMutableSequence();
    TestArrayImmutableSequence();
    TestListImmutableSequence();
    TestQueue();
    TestDeque();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}