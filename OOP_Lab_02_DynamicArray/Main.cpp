#include <iostream>
#include <locale.h>
#include "DynamicArray.h"

using namespace std;

void printArray(const DynamicArray& array)
{
    int arrayLength = array.getLength();

    for (int index = 0; index < arrayLength; index++)
    {
        cout << array[index];

        if (index < arrayLength - 1) cout << ", ";
    }

    cout << std::endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    int testArray1[] = { 1, 2, -1, 5, 3, -6, 3, -6, 0, 53, 36, 35, -30, -41 };

    cout << "1. Создание массива и проверка присваивания\n";
    DynamicArray testDynamicArray1(testArray1, 14);

    testDynamicArray1 = testDynamicArray1;
    cout << "Оригинальный массив: ";
    printArray(testDynamicArray1);

    cout << "\n2. Проверка копирования\n";
    {
        DynamicArray testDynamicArray2;
        testDynamicArray2 = testDynamicArray1;

        int arrayLength = testDynamicArray2.getLength();

        for (int index = 0; index < arrayLength; index++)
        {
            testDynamicArray2[index] += 100;
        }

        cout << "Копия: ";
        printArray(testDynamicArray2);
    }

    cout << "Оригинальный массив после удаления копии: ";
    printArray(testDynamicArray1);

    cout << "\n3. Проверка сортировки (шейкерная)\n";
    testDynamicArray1.sort();
    cout << "Отсортированный массив: ";
    printArray(testDynamicArray1);

    cout << "\n4. Проверка методов поиска, вставки и удаления\n";
    int valueToFind = 53;
    cout << "Индекс элемента [" << valueToFind << "]: " << testDynamicArray1.find(valueToFind) << "\n";

    testDynamicArray1.insertID(0, 999);
    cout << "После вставки 999 в начало: ";
    printArray(testDynamicArray1);

    testDynamicArray1.removeID(5);
    cout << "После удаления элемента по индексу 5: ";
    printArray(testDynamicArray1);

    testDynamicArray1.removeVal(3);
    cout << "После удаления первого значения '3': ";
    printArray(testDynamicArray1);

    cout << "\n5. Проверка метода swap\n";
    int testArray2[] = { 1, 2, 3 };
    DynamicArray testDynamicArray3(testArray2, 3);

    cout << "Массив 1 до: ";
    printArray(testDynamicArray1);
    cout << "Массив 3 до: ";
    printArray(testDynamicArray3);

    testDynamicArray1.swap(testDynamicArray3);

    cout << "Массив 1 после: ";
    printArray(testDynamicArray1);
    cout << "Массив 3 после: ";
    printArray(testDynamicArray3);

    cout << "\n6. Проверка потокового вывода\n";
    cout << testDynamicArray1 << endl;

    return 0;
}