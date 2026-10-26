#pragma once
#include <iostream>

class DynamicArray
{
public:
    class iterator;
    class const_iterator;

    DynamicArray();
    DynamicArray(const int* const arrayData, const int arrayLength);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other);

    int& operator[](const int index);
    const int& operator[](const int index) const;

    int getLength() const;

    void swap(DynamicArray& other);
    int find(int value) const;
    void sort();

    int getMax() const;
    int getMin() const;

    bool insertID(const int index, int value);
    bool removeID(const int index);
    bool removeVal(int value);
    void removeAllVal(int value);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    DynamicArray& operator+=(int value);
    DynamicArray operator+(int value) const;

    DynamicArray& operator+=(const DynamicArray& other);
    DynamicArray operator+(const DynamicArray& other) const;

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    iterator insertIT(iterator pos, int value);
    iterator delIT(iterator pos);
    iterator delIT_InRange(iterator first, iterator last);

private:

    int* arrayData_ = nullptr;
    int arrayLength_ = 0;
};


class DynamicArray::iterator
{
public:

    iterator() = default;
    iterator(int* arrayData, int elementIndex);

    bool operator==(const iterator& otherIterator) const;
    bool operator!=(const iterator& otherIterator) const;
    iterator& operator++();
    iterator operator++(int);
    int& operator*();

    int getIndex() const
    {
        return elementIndex_;
    }

    int* getData() const
    {
        return arrayData_;
    }

private:
    int* arrayData_ = nullptr;
    int elementIndex_ = 0;
};


class DynamicArray::const_iterator
{
public:

    const_iterator() = default;
    const_iterator(const int* arrayData, int elementIndex);

    bool operator==(const const_iterator& otherIterator) const;
    bool operator!=(const const_iterator& otherIterator) const;
    const_iterator& operator++();
    const_iterator operator++(int);
    const int& operator*() const;

    int getIndex() const
    {
        return elementIndex_;
    }

    const int* getData() const
    {
        return arrayData_;
    }

private:
    const int* arrayData_ = nullptr;
    int elementIndex_ = 0;
};

std::ostream& operator<<(std::ostream& os, const DynamicArray& array);
std::istream& operator>>(std::istream& is, DynamicArray& array);