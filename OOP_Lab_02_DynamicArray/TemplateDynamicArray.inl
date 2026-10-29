#include <assert.h>
#include <iostream>

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray() : arrayData_(nullptr), arrayLength_(0)
{

}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const ItemType* const arrayData, const int arrayLength) : arrayLength_(arrayLength)
{
    if (arrayLength_ > 0)
    {
        arrayData_ = new ItemType[arrayLength_];
        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = arrayData[index];
    }
    else
    {
        arrayData_ = nullptr;
        arrayLength_ = 0;
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(const DynamicArray& other)
{
    arrayLength_ = other.arrayLength_;
    if (arrayLength_ > 0)
    {
        arrayData_ = new ItemType[arrayLength_];
        for (int index = 0; index < arrayLength_; index++)
            arrayData_[index] = other.arrayData_[index];
    }
    else
    {
        arrayData_ = nullptr;
    }
}

template<typename ItemType>
DynamicArray<ItemType>::DynamicArray(DynamicArray&& other)
{
    arrayLength_ = other.arrayLength_;
    arrayData_ = other.arrayData_;

    other.arrayLength_ = 0;
    other.arrayData_ = nullptr;
}

template<typename ItemType>
DynamicArray<ItemType>::~DynamicArray()
{
    delete[] arrayData_;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(const DynamicArray& other)
{
    if (this != &other)
    {
        delete[] arrayData_;
        arrayLength_ = other.arrayLength_;

        if (arrayLength_ > 0)
        {
            arrayData_ = new ItemType[arrayLength_];
            for (int index = 0; index < arrayLength_; index++)
                arrayData_[index] = other.arrayData_[index];
        }
        else
        {
            arrayData_ = nullptr;
        }
    }
    return *this;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator=(DynamicArray&& other)
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

template<typename ItemType>
ItemType& DynamicArray<ItemType>::operator[](const int index)
{
    assert((index >= 0 && index < arrayLength_) && "Индекс за пределами массива.");
    return arrayData_[index];
}

template<typename ItemType>
const ItemType& DynamicArray<ItemType>::operator[](const int index) const
{
    assert((index >= 0 && index < arrayLength_) && "Индекс за пределами массива.");
    return arrayData_[index];
}

template<typename ItemType>
int DynamicArray<ItemType>::getLength() const
{
    return arrayLength_;
}

template<typename ItemType>
void DynamicArray<ItemType>::swap(DynamicArray& other)
{
    ItemType* t = arrayData_;
    arrayData_ = other.arrayData_;
    other.arrayData_ = t;

    int t2 = arrayLength_;
    arrayLength_ = other.arrayLength_;
    other.arrayLength_ = t2;
}

template<typename ItemType>
int DynamicArray<ItemType>::find(const ItemType& value) const
{
    for (int index = 0; index < arrayLength_; index++)
    {
        if (arrayData_[index] == value)
            return index;
    }
    return -1;
}

template<typename ItemType>
void DynamicArray<ItemType>::sort()
{
    if (arrayLength_ <= 1)
        return;

    int lt = 0;
    int rt = arrayLength_ - 1;
    bool shifted = true;

    while (lt < rt && shifted)
    {
        shifted = false;

        for (int i = lt; i < rt; i++)
        {
            if (arrayData_[i] > arrayData_[i + 1])
            {
                ItemType t = arrayData_[i];
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
                ItemType t = arrayData_[i];
                arrayData_[i] = arrayData_[i - 1];
                arrayData_[i - 1] = t;
                shifted = true;
            }
        }
        lt++;
    }
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::getMax() const
{
    assert(arrayLength_ > 0 && "Массив пуст.");

    ItemType maxVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] > maxVal)
        {
            maxVal = arrayData_[i];
        }
    }
    return maxVal;
}

template<typename ItemType>
ItemType DynamicArray<ItemType>::getMin() const
{
    assert(arrayLength_ > 0 && "Массив пуст.");

    ItemType minVal = arrayData_[0];
    for (int i = 1; i < arrayLength_; i++)
    {
        if (arrayData_[i] < minVal)
        {
            minVal = arrayData_[i];
        }
    }
    return minVal;
}

template<typename ItemType>
bool DynamicArray<ItemType>::insertID(const int index, const ItemType& value)
{
    if (index < 0 || index > arrayLength_)
        return false;

    ItemType* newBuffer = new ItemType[arrayLength_ + 1];
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

template<typename ItemType>
bool DynamicArray<ItemType>::removeID(const int index)
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

    ItemType* newBuffer = new ItemType[arrayLength_ - 1];

    for (int i = 0; i < index; i++)
        newBuffer[i] = arrayData_[i];

    for (int i = index + 1; i < arrayLength_; i++)
        newBuffer[i - 1] = arrayData_[i];

    delete[] arrayData_;
    arrayData_ = newBuffer;
    arrayLength_--;

    return true;
}

template<typename ItemType>
bool DynamicArray<ItemType>::removeVal(const ItemType& value)
{
    int index = find(value);
    if (index == -1)
        return false;

    return removeID(index);
}

template<typename ItemType>
void DynamicArray<ItemType>::removeAllVal(const ItemType& value)
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

    ItemType* new_data = new ItemType[newLength];
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

template<typename ItemType>
std::ostream& operator<<(std::ostream& os, const DynamicArray<ItemType>& array)
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

template<typename ItemType>
std::istream& operator>>(std::istream& is, DynamicArray<ItemType>& array)
{
    int length = 0;
    std::cout << "   Введите кол-во элементов массива: ";
    is >> length;

    if (length <= 0)
    {
        DynamicArray<ItemType> emptyArray;
        array.swap(emptyArray);
        return is;
    }

    DynamicArray<ItemType> tempArray;
    std::cout << "   Введите элементы через пробел: ";
    for (int i = 0; i < length; i++)
    {
        ItemType val;
        is >> val;
        tempArray.insertID(i, val);
    }

    array.swap(tempArray);
    return is;
}

                                        // ИТЕРАТОРЫ //

template<typename ItemType>
inline typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::begin()
{
    return iterator(arrayData_, 0);
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::end()
{
    return iterator(arrayData_, arrayLength_);
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::begin() const
{
    return const_iterator(arrayData_, 0);
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::end() const
{
    return const_iterator(arrayData_, arrayLength_);
}

template<typename ItemType>
inline DynamicArray<ItemType>::iterator::iterator(ItemType* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{

}

template<typename ItemType>
inline bool DynamicArray<ItemType>::iterator::operator==(const iterator& otherIterator) const
{
    return (arrayData_ == otherIterator.arrayData_) && (elementIndex_ == otherIterator.elementIndex_);
}

template<typename ItemType>
inline bool DynamicArray<ItemType>::iterator::operator!=(const iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::iterator& DynamicArray<ItemType>::iterator::operator++()
{
    ++elementIndex_;
    return *this;
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::iterator::operator++(int)
{
    typename DynamicArray<ItemType>::iterator copy(*this);
    ++elementIndex_;
    return copy;
}

template<typename ItemType>
inline ItemType& DynamicArray<ItemType>::iterator::operator*()
{
    return arrayData_[elementIndex_];
}

template<typename ItemType>
inline DynamicArray<ItemType>::const_iterator::const_iterator(const ItemType* arrayData, int elementIndex)
    : arrayData_(arrayData), elementIndex_(elementIndex)
{

}

template<typename ItemType>
inline bool DynamicArray<ItemType>::const_iterator::operator==(const const_iterator& otherIterator) const
{
    return (arrayData_ == otherIterator.arrayData_) && (elementIndex_ == otherIterator.elementIndex_);
}

template<typename ItemType>
inline bool DynamicArray<ItemType>::const_iterator::operator!=(const const_iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::const_iterator& DynamicArray<ItemType>::const_iterator::operator++()
{
    ++elementIndex_;
    return *this;
}

template<typename ItemType>
inline typename DynamicArray<ItemType>::const_iterator DynamicArray<ItemType>::const_iterator::operator++(int)
{
    typename DynamicArray<ItemType>::const_iterator copy(*this);
    ++elementIndex_;
    return copy;
}

template<typename ItemType>
inline const ItemType& DynamicArray<ItemType>::const_iterator::operator*() const
{
    return arrayData_[elementIndex_];
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const ItemType& value)
{
    ItemType* new_data = new ItemType[arrayLength_ + 1];

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

template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const ItemType& value) const
{
    DynamicArray result(*this);
    result += value;
    return result;
}

template<typename ItemType>
DynamicArray<ItemType>& DynamicArray<ItemType>::operator+=(const DynamicArray& other)
{
    if (other.arrayLength_ == 0) return *this;

    int newLength = arrayLength_ + other.arrayLength_; ItemType* new_data = new ItemType[newLength];

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

template<typename ItemType>
DynamicArray<ItemType> DynamicArray<ItemType>::operator+(const DynamicArray& other) const
{
    DynamicArray result(*this);
    result += other;
    return result;
}

template<typename ItemType>
bool DynamicArray<ItemType>::operator==(const DynamicArray& other) const
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

template<typename ItemType>
bool DynamicArray<ItemType>::operator!=(const DynamicArray& other) const
{
    return !(*this == other);
}

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::insertIT(iterator pos, const ItemType& value)
{
    int index = pos.getIndex();
    assert(index >= 0 && index <= arrayLength_ && "Индекс за пределами массива.");

    ItemType* new_data = new ItemType[arrayLength_ + 1];

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

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::delIT(iterator pos)
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

template<typename ItemType>
typename DynamicArray<ItemType>::iterator DynamicArray<ItemType>::delIT_InRange(iterator first, iterator last)
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