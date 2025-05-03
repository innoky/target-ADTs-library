#pragma once

#include <stdexcept>
#include <algorithm> 
#include <vector>

template <typename T>
class DynamicArray
{
private:
    T *data;
    int size;

    void allocateAndCopy(const T *source, int count)
    {
        data = new T[count];
        std::copy(source, source + count, data);
        size = count;
    }

public:
    
    DynamicArray(int size) : size(size)
    {
        if (size < 0)
            throw std::invalid_argument("Size cannot be negative");
        data = new T[size]();
    }

   
    DynamicArray(const T *items, int count)
    {
        if (count < 0)
            throw std::invalid_argument("Count cannot be negative");
        allocateAndCopy(items, count);
    }

 
    DynamicArray(const DynamicArray<T> &other)
    {
        allocateAndCopy(other.data, other.size);
    }

   
    DynamicArray<T> &operator=(const DynamicArray<T> &other)
    {
        if (this != &other)
        {
            delete[] data;
            allocateAndCopy(other.data, other.size);
        }
        return *this;
    }

 
    ~DynamicArray()
    {
        delete[] data;
    }

  
    T Get(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

   
    void Set(int index, T value)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }


    int GetSize() const
    {
        return size;
    }

 
    void Resize(int newSize)
    {
        if (newSize < 0)
            throw std::invalid_argument("New size cannot be negative");
        T *newData = new T[newSize]();
        int elementsToCopy = std::min(size, newSize);
        for (int i = 0; i < elementsToCopy; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }

    
    T *GetRawData()
    {
        return data;
    }

 
    T &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    std::vector<T> ToVector() const
    {
        std::vector<T> result(size);
        for (int i = 0; i < size; ++i)
        {
            result[i] = data[i];
        }
        return result;
    }

    std::vector<T> GetSubVector(int startIndex, int endIndex) const
    {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex)
            throw std::out_of_range("Invalid indices");

        std::vector<T> result(endIndex - startIndex + 1);
        for (int i = 0; i <= endIndex - startIndex; ++i)
        {
            result[i] = data[startIndex + i];
        }
        return result;
    }
};
