#include <assert.h>
#include "DynamicArray.h"

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
    int count = 0;
    if (!(is >> count) || count < 0)
        return is;

    delete[] array.arrayData_;
    array.arrayLength_ = count;

    if (array.arrayLength_ > 0)
    {
        array.arrayData_ = new int[array.arrayLength_];
        for (int index = 0; index < array.arrayLength_; index++)
        {
            is >> array.arrayData_[index];
        }
    }
    else
    {
        array.arrayData_ = nullptr;
    }

    return is;
}