#include <iostream>
#include <locale.h>

using namespace std;

void RunIntArrayTest();
void RunTempArrayTest();

int main()
{
    setlocale(LC_ALL, "RUS");

    cout << "==================================================\n";
    cout << "[#1] ТЕСТИРОВАНИЕ ЦЕЛОЧИСЛЕННОГО МАССИВА\n";
    cout << "==================================================\n";
    RunIntArrayTest();

    cout << "\n\n==================================================\n";
    cout << "[#2] ТЕСТИРОВАНИЕ ШАБЛОННОГО МАССИВА\n";
    cout << "==================================================\n";
    RunTempArrayTest();

    std::cout << "\n==================================================\n";

    return 0;
}