#include <iostream>
#include <locale.h>

#include "Segment.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    Segment segment1;
    cout << "1) Отрезок: ";
    segment1.print();
    cout << endl;

    cout << "2) Введите координаты (x1 y1 x2 y2): ";
    segment1.read();
    cout << " ";
    segment1.print();
    cout << endl;

    cout << "3) Проверка аксессора: " << "\n";
    cout << "x1 = " << segment1.getX1() << " -> ";
    segment1.setX1(segment1.getX1() + 1.0);
    cout << "x1 = " << segment1.getX1() << "\n";;
    segment1.print();
    cout << endl;

    return 0;
}