#include <assert.h>
#include <iostream>
#include "DynamicArray.h"

DynamicArray::DynamicArray() : arrayData_(nullptr), arrayLength_(0)
{

}

DynamicArray::DynamicArray(const int* const arrayData, const int arrayLength) : arrayLength_(arrayLength)
{
    arrayData_ = new int[arrayLength_];

    for (int index = 0; index < arrayLength_; index++)
        arrayData_[index] = arrayData[index];
}

DynamicArray::DynamicArray(const DynamicArray& other)
{
    arrayLength_ = other.arrayLength_;

    arrayData_ = new int[arrayLength_];

    for (int index = 0; index < arrayLength_; index++)
        arrayData_[index] = other.arrayData_[index];
}

DynamicArray::DynamicArray(DynamicArray&& other)
{
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = 0;

    arrayData_ = other.arrayData_;
    other.arrayData_ = nullptr;
}

DynamicArray::~DynamicArray()
{
    delete[] arrayData_;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
    if (this != &other)
    {
        delete[] arrayData_;

        arrayLength_ = other.arrayLength_;

        arrayData_ = new int[arrayLength_];

        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = other.arrayData_[index];
    }

    return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other)
{
    if (this != &other)
    {
        delete[] arrayData_;

        arrayLength_ = other.arrayLength_;
        other.arrayLength_ = 0;

        arrayData_ = other.arrayData_;
        other.arrayData_ = nullptr;
    }

    return *this;
}


int& DynamicArray::operator[](const int index)
{
    assert((index >= 0 && index < arrayLength_) && "Индекс за пределами массива.");
    return arrayData_[index];
}

const int& DynamicArray::operator[](const int index) const
{
    assert((index >= 0 && index < arrayLength_) && "Индекс за пределами массива.");
    return arrayData_[index];
}

int DynamicArray::getLength() const
{
    return arrayLength_;
}

void DynamicArray::swap(DynamicArray& other)
{
    int* t = arrayData_;
    arrayData_ = other.arrayData_;
    other.arrayData_ = t;

    int t2 = arrayLength_;
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = t2;
}

int DynamicArray::find(int value) const
{
    for (int index = 0; index < arrayLength_; index++)
    {
        if (arrayData_[index] == value)
            return index;
    }
    return (-1);
}

void DynamicArray::sort()  //шейкерная
{
    if (arrayLength_ <= 1)
        return;

    int lt = 0;
    int rt = arrayLength_ - 1;
    bool swap = true;

    while (lt < rt && swap)
    {
        swap = false;

        for (int i = lt; i < rt; i++)
        {
            if (arrayData_[i] > arrayData_[i + 1])
            {
                int t = arrayData_[i];
                arrayData_[i] = arrayData_[i + 1];
                arrayData_[i + 1] = t;

                swap = true;
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

                swap = true;
            }
        }
        lt++;
    }
}

int DynamicArray::getMax() const
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

int DynamicArray::getMin() const
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

bool DynamicArray::insertID(const int index, int value)
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

bool DynamicArray::removeID(const int index)
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

bool DynamicArray::removeVal(int value)
{
    int index = find(value);
    if (index == -1)
        return false;

    return removeID(index);
}

void DynamicArray::removeAllVal(int value)
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

std::ostream& operator<<(std::ostream& os, const DynamicArray& array)
{
    if (array.arrayLength_ == 0)
    {
        os << "[]";
        return os;
    }

    os << "[";

    for (int index = 0; index < array.arrayLength_; index++)
    {
        os << array.arrayData_[index];
        if (index < array.arrayLength_ - 1)
            os << ", ";
    }

    os << "]";

    return os;
}

std::istream& operator>>(std::istream& is, DynamicArray& array)
{
    int length = 0;
    std::cout << "   Введите кол-во элементов массива: ";
    is >> length;

    if (length <= 0)
    {
        delete[] array.arrayData_;
        array.arrayData_ = nullptr;
        array.arrayLength_ = 0;
        return is;
    }

    int* new_data = new int[length];
    std::cout << "   Введите элементы через пробел: ";
    for (int i = 0; i < length; i++)
    {
        is >> new_data[i];
    }

    delete[] array.arrayData_;
    array.arrayData_ = new_data;
    array.arrayLength_ = length;

    return is;
}

                                    // ИТЕРАТОРЫ //

DynamicArray::iterator::iterator(int* arrayData, int elementIndex) : arrayData_(arrayData), elementIndex_(elementIndex)
{

}

DynamicArray::iterator DynamicArray::begin()
{
    return iterator(arrayData_, 0);
}

DynamicArray::iterator DynamicArray::end()
{
    return iterator(arrayData_, arrayLength_);
}

bool DynamicArray::iterator::operator!=(const DynamicArray::iterator& otherIterator)
{
    if (arrayData_ != otherIterator.arrayData_) return true;
    return elementIndex_ != otherIterator.elementIndex_;
}

DynamicArray::iterator& DynamicArray::iterator::operator++()
{
    ++elementIndex_;

    return *this;
}

DynamicArray::iterator DynamicArray::iterator::operator++(int)
{
    DynamicArray::iterator copy(*this);

    ++elementIndex_;

    return copy;
}

int& DynamicArray::iterator::operator*()
{
    return arrayData_[elementIndex_];
}

DynamicArray& DynamicArray::operator+=(int value)
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

DynamicArray DynamicArray::operator+(int value) const
{
    DynamicArray result(*this);
    result += value;
    return result;
}

DynamicArray& DynamicArray::operator+=(const DynamicArray& other)
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
        new_data[arrayLength_ + i] = other.arrayData_[i];
    }

    delete[] arrayData_;
    arrayData_ = new_data;
    arrayLength_ = newLength;

    return *this;
}

DynamicArray DynamicArray::operator+(const DynamicArray& other) const
{
    DynamicArray result(*this);
    result += other;
    return result;
}

bool DynamicArray::operator==(const DynamicArray& other) const
{
    if (arrayLength_ != other.arrayLength_) return false;

    for (int i = 0; i < arrayLength_; i++)
    {
        if (arrayData_[i] != other.arrayData_[i])
        {
            return false;
        }
    }
    return true;
}

bool DynamicArray::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}


DynamicArray::iterator DynamicArray::insertIT(iterator pos, int value)
{
    int index = pos.elementIndex_;
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


DynamicArray::iterator DynamicArray::delIT(iterator pos)
{
    int index = pos.elementIndex_;
    assert(index >= 0 && index < arrayLength_ && "Индекс за пределами массива.");

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

DynamicArray::iterator DynamicArray::delIT_InRange(iterator first, iterator last)
{
    int firstIdx = first.elementIndex_;
    int lastIdx = last.elementIndex_;

    assert(firstIdx >= 0 && lastIdx <= arrayLength_ && firstIdx <= lastIdx);

    int numToDelete = lastIdx - firstIdx;

    if (numToDelete == 0) 
        return first;

    for (int i = lastIdx; i < arrayLength_; i++) 
    {
        arrayData_[i - numToDelete] = arrayData_[i];
    }

    arrayLength_ -= numToDelete;

    return iterator(arrayData_, firstIdx);
}

bool DynamicArray::iterator::operator==(const iterator& otherIterator) const
{
    return (arrayData_ == otherIterator.arrayData_) && (elementIndex_ == otherIterator.elementIndex_);
}