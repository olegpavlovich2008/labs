#pragma once
#include <iostream>

template<typename ItemType>
class DynamicArray
{
public:
    class iterator;
    class const_iterator;

    DynamicArray();
    DynamicArray(const ItemType* const arrayData, const int arrayLength);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& other);
    DynamicArray& operator=(DynamicArray&& other);

    ItemType& operator[](const int index);
    const ItemType& operator[](const int index) const;

    int getLength() const;

    void swap(DynamicArray& other);
    int find(const ItemType& value) const;
    void sort();

    ItemType getMax() const;
    ItemType getMin() const;

    bool insertID(const int index, const ItemType& value);
    bool removeID(const int index);
    bool removeVal(const ItemType& value);
    void removeAllVal(const ItemType& value);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    DynamicArray& operator+=(const ItemType& value);
    DynamicArray operator+(const ItemType& value) const;

    DynamicArray& operator+=(const DynamicArray& other);
    DynamicArray operator+(const DynamicArray& other) const;

    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    iterator insertIT(iterator pos, const ItemType& value);
    iterator delIT(iterator pos);
    iterator delIT_InRange(iterator first, iterator last);

private:

    ItemType* arrayData_ = nullptr;
    int arrayLength_ = 0;
};


template<typename ItemType>
class DynamicArray<ItemType>::iterator
{
public:

    iterator() = default;
    iterator(ItemType* arrayData, int elementIndex);

    bool operator==(const iterator& otherIterator) const;
    bool operator!=(const iterator& otherIterator) const;
    iterator& operator++();
    iterator operator++(int);
    ItemType& operator*();

    int getIndex() const
    {
        return elementIndex_;
    }

    ItemType* getData() const
    {
        return arrayData_;
    }

private:
    ItemType* arrayData_ = nullptr;
    int elementIndex_ = 0;
};


template<typename ItemType>
class DynamicArray<ItemType>::const_iterator
{
public:

    const_iterator() = default;
    const_iterator(const ItemType* arrayData, int elementIndex);

    bool operator==(const const_iterator& otherIterator) const;
    bool operator!=(const const_iterator& otherIterator) const;
    const_iterator& operator++();
    const_iterator operator++(int);
    const ItemType& operator*() const;

    int getIndex() const
    {
        return elementIndex_;
    }

    const ItemType* getData() const
    {
        return arrayData_;
    }

private:
    const ItemType* arrayData_ = nullptr;
    int elementIndex_ = 0;
};

template<typename ItemType>
std::ostream& operator<<(std::ostream& os, const DynamicArray<ItemType>& array);
template<typename ItemType>
std::istream& operator>>(std::istream& is, DynamicArray<ItemType>& array);

#include "DynamicArray.inl"