#include <assert.h>
#include <iostream>
#include "IntDynamicArray.h"

IntDynamicArray::IntDynamicArray() : arrayData_(nullptr), arrayLength_(0)
{
}

IntDynamicArray::IntDynamicArray(const int* const arrayData, const int arrayLength) : arrayLength_(arrayLength)
{
    if (arrayLength_ > 0)
    {
        arrayData_ = new int[arrayLength_];
        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = arrayData[index];
    }
    else
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
    }
}

IntDynamicArray::IntDynamicArray(const IntDynamicArray& other)
{
    arrayLength_ = other.arrayLength_;
    if (arrayLength_ > 0)
    {
        arrayData_ = new int[arrayLength_];
        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = other.arrayData_[index];
    }
    else
    {
        arrayData_ = nullptr;
    }
}

IntDynamicArray::IntDynamicArray(IntDynamicArray&& other)
{
    arrayLength_ = other.arrayLength_;
    arrayData_ = other.arrayData_;

    other.arrayLength_ = 0;
    other.arrayData_ = nullptr;
}

IntDynamicArray::~IntDynamicArray()
{
    delete[] arrayData_;
}

IntDynamicArray& IntDynamicArray::operator=(const IntDynamicArray& other)
{
    if (this != &other)
    {
        if (other.arrayLength_ > 0)
        {
            // Безопасное выделение памяти перед очисткой старой
            int* newBuffer = new int[other.arrayLength_];
            for (int index = 0; index < other.arrayLength_; index++)
                newBuffer[index] = other.arrayData_[index];

            delete[] arrayData_;
            arrayData_ = newBuffer;
            arrayLength_ = other.arrayLength_;
        }
        else
        {
            delete[] arrayData_;
            arrayData_ = nullptr;
            arrayLength_ = 0;
        }
    }
    return *this;
}

IntDynamicArray& IntDynamicArray::operator=(IntDynamicArray&& other)
{
    if (this != &other)
    {
        delete[] arrayData_;

        arrayLength_ = other.arrayLength_;
        arrayData_ = other.arrayData_;

        other.arrayLength_ = 0;
        other.arrayData_ = nullptr;
    }
    return *this;
}

int& IntDynamicArray::operator[](const int index)
{
    assert((index >= 0 && index < arrayLength_) && "Индекс за пределами массива.");
    return arrayData_[index];
}

const int& IntDynamicArray::operator[](const int index) const
{
    assert((index >= 0 && index < arrayLength_) && "Индекс за пределами массива.");
    return arrayData_[index];
}

int IntDynamicArray::getLength() const
{
    return arrayLength_;
}

void IntDynamicArray::swap(IntDynamicArray& other)
{
    int* t = arrayData_;
    arrayData_ = other.arrayData_;
    other.arrayData_ = t;

    int t2 = arrayLength_;
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = t2;
}

int IntDynamicArray::find(int value) const
{
    for (int index = 0; index < arrayLength_; index++)
    {
        if (arrayData_[index] == value)
            return index;
    }
    return -1;
}

void IntDynamicArray::sort() // шейкерная
{
    if (arrayLength_ <= 1)
        return;

    int lt = 0;
    int rt = arrayLength_ - 1;
    bool shifted = true;

    while (lt < rt&& shifted)
    {
        shifted = false;

        for (int i = lt; i < rt; i++)
        {
            if (arrayData_[i] > arrayData_[i + 1])
            {
                int t = arrayData_[i];
                arrayData_[i] = arrayData_[i + 1];
                arrayData_[i + 1] = t;
                shifted = true;
            }
        }
        rt--;

        for (int i = rt; i > lt; i--)
        {
            if (arrayData_[i - 1] > arrayData_[i])
            {
                int t = arrayData_[i];
                arrayData_[i] = arrayData_[i - 1];
                arrayData_[i - 1] = t;
                shifted = true;
            }
        }
        lt++;
    }
}

int IntDynamicArray::getMax() const
{
    assert(arrayLength_ > 0 && "Массив пуст.");

    int maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] > maxVal)
        {
            maxVal = arrayData_[i];
        }
    }
    return maxVal;
}

int IntDynamicArray::getMin() const
{
    assert(arrayLength_ > 0 && "Массив пуст.");

    int minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] < minVal)
        {
            minVal = arrayData_[i];
        }
    }
    return minVal;
}

bool IntDynamicArray::insertID(const int index, int value)
{
    if (index < 0 || index > arrayLength_)
        return false;

    int* newBuffer = new int[arrayLength_ + 1];
    for (int i = 0; i < index; i++)
        newBuffer[i] = arrayData_[i];

    newBuffer[index] = value;

    for (int i = index; i < arrayLength_; i++)
        newBuffer[i + 1] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = newBuffer;
    arrayLength_++;

    return true;
}

bool IntDynamicArray::removeID(const int index)
{
    if (index < 0 || index >= arrayLength_)
        return false;

    if (arrayLength_ == 1)
    {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return true;
    }

    int* newBuffer = new int[arrayLength_ - 1];

    for (int i = 0; i < index; i++)
        newBuffer[i] = arrayData_[i];

    for (int i = index + 1; i < arrayLength_; i++)
        newBuffer[i - 1] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = newBuffer;
    arrayLength_--;

    return true;
}

bool IntDynamicArray::removeVal(int value)
{
    int index = find(value);
    if (index == -1)
        return false;

    return removeID(index);
}

void IntDynamicArray::removeAllVal(int value)
{
    int countToDelete = 0;
    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] == value)
        {
            countToDelete++;
        }
    }

    if (countToDelete == 0)
        return;

    int newLength = arrayLength_ - countToDelete;

    if (newLength == 0)
    {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return;
    }

    int* new_data = new int[newLength];
    int newIndex = 0;

    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] != value)
        {
            new_data[newIndex++] = arrayData_[i];
        }
    }

    delete[] arrayData_;
    arrayData_ = new_data;
    arrayLength_ = newLength;
}

std::ostream& operator<<(std::ostream& os, const IntDynamicArray& array)
{
    int len = array.getLength();
    if (len == 0)
    {
        os << "[]";
        return os;
    }

    os << "[";
    for (int index = 0; index < len; index++)
    {
        os << array[index];
        if (index < len - 1)
            os << ", ";
    }
    os << "]";

    return os;
}

std::istream& operator>>(std::istream& is, IntDynamicArray& array)
{
    int length = 0;
    std::cout << "   Введите кол-во элементов массива: ";
    is >> length;

    if (length <= 0)
    {
        IntDynamicArray emptyArray;
        array.swap(emptyArray);
        return is;
    }

    IntDynamicArray tempArray;
    std::cout << "   Введите элементы через пробел: ";
    for (int i = 0; i < length; i++)
    {
        int val;
        is >> val;
        tempArray.insertID(i, val);
    }

    array.swap(tempArray);
    return is;
}

// ИТЕРАТОРЫ //

IntDynamicArray::iterator::iterator(int* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{
}

IntDynamicArray::iterator IntDynamicArray::begin()
{
    return iterator(arrayData_, 0);
}

IntDynamicArray::iterator IntDynamicArray::end()
{
    return iterator(arrayData_, arrayLength_);
}

bool IntDynamicArray::iterator::operator==(const iterator& otherIterator) const
{
    return (arrayData_ == otherIterator.arrayData_) && (elementIndex_ == otherIterator.elementIndex_);
}

bool IntDynamicArray::iterator::operator!=(const iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

IntDynamicArray::iterator& IntDynamicArray::iterator::operator++()
{
    ++elementIndex_;
    return *this;
}

IntDynamicArray::iterator IntDynamicArray::iterator::operator++(int)
{
    IntDynamicArray::iterator copy(*this);
    ++elementIndex_;
    return copy;
}

int& IntDynamicArray::iterator::operator*()
{
    return arrayData_[elementIndex_];
}

IntDynamicArray::const_iterator::const_iterator(const int* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{
}

IntDynamicArray::const_iterator IntDynamicArray::begin() const
{
    return const_iterator(arrayData_, 0);
}

IntDynamicArray::const_iterator IntDynamicArray::end() const
{
    return const_iterator(arrayData_, arrayLength_);
}

bool IntDynamicArray::const_iterator::operator==(const const_iterator& otherIterator) const
{
    return (arrayData_ == otherIterator.arrayData_) && (elementIndex_ == otherIterator.elementIndex_);
}

bool IntDynamicArray::const_iterator::operator!=(const const_iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

IntDynamicArray::const_iterator& IntDynamicArray::const_iterator::operator++()
{
    ++elementIndex_;
    return *this;
}

IntDynamicArray::const_iterator IntDynamicArray::const_iterator::operator++(int)
{
    IntDynamicArray::const_iterator copy(*this);
    ++elementIndex_;
    return copy;
}

const int& IntDynamicArray::const_iterator::operator*() const
{
    return arrayData_[elementIndex_];
}

IntDynamicArray& IntDynamicArray::operator+=(int value)
{
    int* new_data = new int[arrayLength_ + 1];

    for (int i = 0; i < arrayLength_; i++)
    {
        new_data[i] = arrayData_[i];
    }

    new_data[arrayLength_] = value;

    delete[] arrayData_;
    arrayData_ = new_data;
    arrayLength_++;

    return *this;
}

IntDynamicArray IntDynamicArray::operator+(int value) const
{
    IntDynamicArray result(*this);
    result += value;
    return result;
}

IntDynamicArray& IntDynamicArray::operator+=(const IntDynamicArray& other)
{
    if (other.arrayLength_ == 0) return *this;

    int newLength = arrayLength_ + other.arrayLength_;
    int* new_data = new int[newLength];

    for (int i = 0; i < arrayLength_; i++)
    {
        new_data[i] = arrayData_[i];
    }

    for (int i = 0; i < other.arrayLength_; i++)
    {
        new_data[arrayLength_ + i] = other[i];
    }

    delete[] arrayData_;
    arrayData_ = new_data;
    arrayLength_ = newLength;

    return *this;
}

IntDynamicArray IntDynamicArray::operator+(const IntDynamicArray& other) const
{
    IntDynamicArray result(*this);
    result += other;
    return result;
}

bool IntDynamicArray::operator==(const IntDynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;

    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] != other[i])
        {
            return false;
        }
    }
    return true;
}

bool IntDynamicArray::operator!=(const IntDynamicArray& other) const
{
    return !(*this == other);
}

IntDynamicArray::iterator IntDynamicArray::insertIT(iterator pos, int value)
{
    int index = pos.getIndex();
    assert(index >= 0 && index <= arrayLength_ && "Индекс за пределами массива.");

    int* new_data = new int[arrayLength_ + 1];

    for (int i = 0; i < index; i++)
    {
        new_data[i] = arrayData_[i];
    }

    new_data[index] = value;

    for (int i = index; i < arrayLength_; i++)
    {
        new_data[i + 1] = arrayData_[i];
    }

    delete[] arrayData_;
    arrayData_ = new_data;
    arrayLength_++;

    return iterator(arrayData_, index);
}

IntDynamicArray::iterator IntDynamicArray::delIT(iterator pos)
{
    int index = pos.getIndex();
    assert(index >= 0 && index < arrayLength_ && "Индекс за пределами массива.");

    if (arrayLength_ == 1)
    {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return end();
    }

    if (index == arrayLength_ - 1)
    {
        arrayLength_--;
        return end();
    }

    for (int i = index; i < arrayLength_ - 1; i++)
    {
        arrayData_[i] = arrayData_[i + 1];
    }
    arrayLength_--;

    return iterator(arrayData_, index);
}

IntDynamicArray::iterator IntDynamicArray::delIT_InRange(iterator first, iterator last)
{
    int firstIdx = first.getIndex();
    int lastIdx = last.getIndex();

    assert(firstIdx >= 0 && lastIdx <= arrayLength_ && firstIdx <= lastIdx);

    int numToDelete = lastIdx - firstIdx;

    if (numToDelete == 0)
        return first;

    if (arrayLength_ == numToDelete)
    {
        delete[] arrayData_;
        arrayData_ = nullptr;
        arrayLength_ = 0;
        return end();
    }

    for (int i = lastIdx; i < arrayLength_; i++)
    {
        arrayData_[i - numToDelete] = arrayData_[i];
    }

    arrayLength_ -= numToDelete;

    return iterator(arrayData_, firstIdx);
}