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

    cout << "3) Проверка аксессора: " << endl;
    cout << "x1 = " << segment1.getX1() << " -> ";
    segment1.setX1(segment1.getX1() + 1.0);
    cout << "x1 = " << segment1.getX1() << endl;
    segment1.setX1(segment1.getX1() - 1.0);
    segment1.print();
    cout << endl;

    cout << "4) Длина отрезка = " << segment1.length() << endl;

    double lambda = 1.0;
    cout << "5) Точка (лямбда " << lambda << ") = ";
    segment1.printPointInRatio(lambda);
    cout << endl;

    Segment segment2(0.0, 0.0, 3.0, 4.0);
    cout << "6) Отрезок 2: ";
    segment2.print();
    cout << " Равны: ";
    if (segment1 == segment2) cout << "Да." << endl;
    else cout << "Нет" << endl;

    cout << "7) Параллелен Ox: ";
    if (segment1.isParallelToOx()) cout << "Да" << endl;
    else cout << "Нет" << endl;

    cout << "8) Параллельны между собой: ";
    if (segment1.isParallelTo(segment2)) cout << "Да" << endl;
    else cout << "Нет" << endl;

    cout << "9) Пересекает Oy: ";
    if (segment1.intersectsOy()) cout << "Да" << endl;
    else cout << "Нет" << endl;

    return 0;
}