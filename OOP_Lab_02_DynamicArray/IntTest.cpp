#include <iostream>
#include <locale.h>
#include "IntDynamicArray.h"

using namespace std;

void printArray(const IntDynamicArray& array)
{
    int arrayLength = array.getLength();

    cout << "[";
    for (int index = 0; index < arrayLength; index++)
    {
        cout << array[index];

        if (index < arrayLength - 1) cout << ", ";
    }

    cout << "]" << std::endl;
}

void RunIntArrayTest()
{
    setlocale(LC_ALL, "RUS");

    int testArray1[] = { 1, 2, -1, 5, 3, -6, 3, -6, 0, 53, 36, 35, -30, -41 };

    cout << "=== ТЕСТИРОВАНИЕ ИТЕРАТОРОВ ===\n" << endl;
    IntDynamicArray iteratorTestArray(testArray1, 5);

    cout << "1) Тестовый массив: ";
    printArray(iteratorTestArray);

    cout << "\n2) Обход через итераторы: ";
    IntDynamicArray::iterator it = iteratorTestArray.begin();
    IntDynamicArray::iterator endIt = iteratorTestArray.end();
    while (it != endIt)
    {
        cout << *it << " ";
        ++it;
    }
    cout << "\n";

    cout << "\n3) Модификация первого элемента: ";
    it = iteratorTestArray.begin();
    *it = 999;
    printArray(iteratorTestArray);

    cout << "\n4) Тест постфиксного инкремента: " << endl;
    it = iteratorTestArray.begin();
    IntDynamicArray::iterator oldIt = it++;
    cout << "   Значение старого итератора: " << *oldIt << endl;
    cout << "   Значение нового итератора: " << *it << endl;

    cout << "   Вывод (range-based for): ";
    for (int& value : iteratorTestArray)
    {
        cout << value << " ";
    }
    cout << endl;

    cout << "\n5) Тест операторов + и +=: \n";
    IntDynamicArray arrOp;
    arrOp += 10;
    arrOp += 20;
    cout << "   После += 10 и += 20: " << arrOp << endl;

    IntDynamicArray arrOp2 = arrOp + 30;
    cout << "   Новый массив (arrOp + 30): " << arrOp2 << endl;

    cout << "\n6) Тест вставки элемента перед итератором: ";

    IntDynamicArray::iterator itInsert = arrOp2.begin();
    ++itInsert;
    arrOp2.insertIT(itInsert, 999);
    cout << arrOp2 << endl;

    cout << "\n7) Тест удаления элемента и диапазона через итераторы: \n";

    IntDynamicArray::iterator itErase = arrOp2.begin();
    ++itErase;
    arrOp2.delIT(itErase);
    cout << "   После удаления элемента 999: " << arrOp2 << endl;

    IntDynamicArray::iterator firstDel = arrOp2.begin();
    IntDynamicArray::iterator lastDel = arrOp2.begin();
    ++lastDel; ++lastDel;

    arrOp2.delIT_InRange(firstDel, lastDel);
    cout << "   После удаления первых двух элементов: " << arrOp2 << endl;

    cout << "\n=== ТЕСТИРОВАНИЕ ОСНОВНЫХ МЕТОДОВ ===\n" << endl;

    cout << "1) Создание массива и проверка присваивания: ";
    IntDynamicArray testDynamicArray1(testArray1, 14);

    testDynamicArray1 = testDynamicArray1;
    printArray(testDynamicArray1);

    cout << "\n2) Копирование массива:\n";
    {
        IntDynamicArray testDynamicArray2;
        testDynamicArray2 = testDynamicArray1;

        int arrayLength = testDynamicArray2.getLength();

        for (int index = 0; index < arrayLength; index++)
        {
            testDynamicArray2[index] += 100;
        }

        cout << "   Копия (+= 100): ";
        printArray(testDynamicArray2);
    }

    cout << "   Оригинал после удаления копии: ";
    printArray(testDynamicArray1);

    cout << "\n3) Сортировка (шейкерная): ";
    testDynamicArray1.sort();
    printArray(testDynamicArray1);

    testDynamicArray1 = IntDynamicArray(testArray1, 14);

    cout << "\n4) Поиск, вставка и удаление элементов: \n";
    int valueToFind = 53;
    cout << "   Индекс элемента [" << valueToFind << "]: " << testDynamicArray1.find(valueToFind) << "\n";

    IntDynamicArray copyTestArray = testDynamicArray1;

    copyTestArray.insertID(0, 999);
    cout << "   После вставки 999 в начало: ";
    printArray(copyTestArray);

    copyTestArray.removeID(5);
    cout << "   После удаления элемента по индексу 5: ";
    printArray(copyTestArray); copyTestArray.removeVal(3);
    cout << "   После удаления первого элемента со значением 3: ";
    printArray(copyTestArray);

    cout << "\n5) Проверка поиска минимума/максимума: \n";
    cout << "   Максимальный элемент: " << testDynamicArray1.getMax() << endl;
    cout << "   Минимальный элемент: " << testDynamicArray1.getMin() << endl;

    cout << "\n6) Удаления всех элементов с заданным значением: \n";
    int dublicateArray[] = { 7, 1, 7, 7, 3, 7, 5 };
    IntDynamicArray testDublicates(dublicateArray, 7);
    cout << "   Массив до удаления: " << testDublicates << endl;
    testDublicates.removeAllVal(7);
    cout << "   Массив после удаления всех элементов со значением 7: " << testDublicates << endl;

    cout << "\n7) Проверка метода swap: \n";
    int testArray2[] = { 1, 15, 90 };
    IntDynamicArray testDynamicArray3(testArray2, 3);

    cout << "   Массив A до: "; printArray(testDynamicArray1);
    cout << "   Массив B до: "; printArray(testDynamicArray3);
    cout << endl;

    testDynamicArray1.swap(testDynamicArray3);

    cout << "   Массив A после: "; printArray(testDynamicArray1);
    cout << "   Массив B после: "; printArray(testDynamicArray3);

    cout << "\n8) Конкатенации массивов и сравнения (==, !=, +, +=): \n";
    int part1[] = { 1, 2 };
    int part2[] = { 3, 4 };
    IntDynamicArray arrA(part1, 2);
    IntDynamicArray arrB(part2, 2);

    cout << "   Массив А: " << arrA << endl;
    cout << "   Массив B: " << arrB << endl;

    IntDynamicArray arrC = arrA + arrB;
    cout << "   Результат сложения A + B = C: " << arrC << endl;

    arrA += arrB;
    cout << "   Результат после A += B: " << arrA << endl;

    cout << "   Оператор равенства (A == C): " << (arrA == arrC ? "Равны" : "Не равны") << endl;
    cout << "   Оператора неравенства (A != B): " << (arrA != arrB ? "Не равны" : "Равны") << endl;

    cout << "\n9) Проверка потокового ввода и вывода: \n";
    IntDynamicArray userArray;

    cin >> userArray;

    cout << "   Пользовательский массив: " << userArray << endl;
}