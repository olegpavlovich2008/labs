#pragma once
#include <iostream>

class DynamicArray
{
    public:

        DynamicArray() = default;
        DynamicArray(const int* const arrayData, const int arrayLength);
        DynamicArray(const DynamicArray& other);
        ~DynamicArray();

        DynamicArray& operator=(const DynamicArray& other);

        int& operator[](const int index);
        const int& operator[](const int index) const;


        int getLength() const;

        void swap(DynamicArray& other);

        int find(int value) const;

        void sort();

        bool insertID(const int index, int value);

        bool removeID(const int index);

        bool removeVal(int value);

        friend std::ostream& operator<<(std::ostream& os, const DynamicArray& array);
        friend std::istream& operator>>(std::istream& is, DynamicArray& array);

    private:

        int* arrayData_ = nullptr;
        int arrayLength_ = 0;

};