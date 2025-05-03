#include "SequenceUI.hpp"
#include <iostream>

void SequenceUI::Run()
{
    while (true)
    {
        PrintMenu();
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            HandleMutableSequence<ArrayMutableSequence<int>>();
            break;
        case 2:
            HandleMutableSequence<ListMutableSequence<int>>();
            break;
        case 3:
            HandleImmutableSequence<ArrayImmutableSequence<int>>();
            break;
        case 4:
            HandleImmutableSequence<ListImmutableSequence<int>>();
            break;
        case 0:
            std::cout << "Выходим...\n";
            return;
        default:
            std::cout << "Неверный выбор. Попробуйте еще.\n";
            break;
        }
    }
}

void SequenceUI::PrintMenu()
{
    std::cout << "\nВыберите тип последовательности:\n";
    std::cout << "1. ArrayMutableSequence\n";
    std::cout << "2. ListMutableSequence\n";
    std::cout << "3. ArrayImmutableSequence\n";
    std::cout << "4. ListImmutableSequence\n";
    std::cout << "0. Выйти\n";
    std::cout << "Введите выбор: ";
}

template <typename SeqType>
void SequenceUI::HandleMutableSequence()
{
    SeqType seq;
    std::cout << "Мутирующая последовательность создана. Введие числа (для окончания -1): ";

    int val;
    while (std::cin >> val && val != -1)
    {
        seq.AppendInPlace(val);
    }

    std::cout << "Длина: " << seq.GetLength() << "\n";
    std::cout << "Первый элемент: " << seq.GetFirst() << ", Последний элемент: " << seq.GetLast() << "\n";

    std::cout << "Вставляем в конец 999...\n";
    seq.AppendInPlace(999);
    std::cout << "Новый последний элемент: " << seq.GetLast() << "\n";
}

template <typename SeqType>
void SequenceUI::HandleImmutableSequence()
{
    std::vector<int> items;
    std::cout << "Немутирующая последовательность создана. Введие числа (для окончания -1): ";

    int val;
    while (std::cin >> val && val != -1)
    {
        items.push_back(val);
    }

    auto seq = std::make_unique<SeqType>(items.data(), static_cast<int>(items.size()));

    std::cout << "Длина: " << seq->GetLength() << "\n";
    std::cout << "Первый элемент: " << seq->GetFirst() << ", Последний элемент: " << seq->GetLast() << "\n";

    std::cout << "Вставляем в конец 999... (возвращает новую последовательность)\n";
    auto newSeq = seq->Append(999);
    std::cout << "Изначальный последний элемент: " << seq->GetLast() << ", Новый последний элемент: " << newSeq->GetLast() << "\n";
}


template void SequenceUI::HandleMutableSequence<ArrayMutableSequence<int>>();
template void SequenceUI::HandleMutableSequence<ListMutableSequence<int>>();
template void SequenceUI::HandleImmutableSequence<ArrayImmutableSequence<int>>();
template void SequenceUI::HandleImmutableSequence<ListImmutableSequence<int>>();
