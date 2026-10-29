#include <iostream>
#include <vector>
#include <locale.h>
#include "Lib.h"


int main() 
{
    setlocale(LC_ALL, "RUS");

    vector<int> arr = { 45, -7, 12, 89, 0, 3, -15, 21, 64, 7, 33, 19, 1, -5, 42 };

    vector<int> h = { 7, 3, 1 };

    cout << "Исходный массив: ";
    PrintArr(arr);

    ShellSort(arr, h);

    cout << "Отсортированный массив: ";
    PrintArr(arr);

    if (Sorted(arr)) 
    {
        cout << "Массив упорядочен.\n";
    }
    else 
    {
        cout << "Массив неупорядочен.\n";
    }

    return 0;
}