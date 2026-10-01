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

    cout << endl;

    cout << "2) Введите координаты (x1 y1 x2 y2): ";
    segment1.read();
    cout << " ";
    segment1.print();
    cout << endl;

    cout << endl;

    cout << "3) Проверка аксессора: " << endl;
    cout << "x1 = " << segment1.getX1() << " -> ";
    segment1.setX1(segment1.getX1() + 1.0);
    cout << "x1 = " << segment1.getX1() << endl;
    segment1.setX1(segment1.getX1() - 1.0);
    segment1.print();
    cout << endl;

    cout << endl;

    cout << "4) Длина отрезка = " << segment1.length() << endl;

    cout << endl;

    double a = 1.0;
    double b = 2.0;
    double lambda = a / b;
    cout << "5) Точка, делящая отрезок в отношении " << a << ":" << b << " = ";
    segment1.printPointInRatio(lambda);
    cout << endl;

    cout << endl;

    Segment segment2(0.0, 0.0, 3.0, 4.0);
    cout << "6) Отрезок 2: ";
    segment2.print();
    cout << endl;
    cout << "Равны: ";
    if (segment1 == segment2) cout << "Да." << endl;
    else cout << "Нет." << endl;

    cout << endl;

    cout << "7) Параллелен Ox: ";
    if (segment1.isParallelToOx()) cout << "Да." << endl;
    else cout << "Нет." << endl;

    cout << endl;

    cout << "8) Параллельны между собой: ";
    if (segment1.isParallelTo(segment2)) cout << "Да." << endl;
    else cout << "Нет." << endl;

    cout << endl;

    cout << "9) Пересекает Oy: ";
    if (segment1.intersectsOy()) cout << "Да." << endl;
    else cout << "Нет." << endl;

    cout << endl;

    double A = 1.0, B = 1.0, C = -4.0;
    cout << "10) Пересекает прямую (" << A << "x + " << B << "y + " << C << " = 0): ";
    if (segment1.intersectsLine(A, B, C)) cout << "Да." << endl;
    else cout << "Нет." << endl;

    cout << endl;

    double px = 2.0, py = 2.0;
    cout << "11) Точка (" << px << ", " << py << ") лежит на отрезке: ";
    if (segment1.containsPoint(px, py)) cout << "Да." << endl;
    else cout << "Нет." << endl;

    cout << endl;

    double checkX = 1.0, checkY = 4.0 / 3.0;     //0 0 3 4 - координаты для проверки, должно совпасть с отношением в пункте 5)//
    cout << "12) Отношение для точки (" << checkX << ", " << checkY << ") = ";
    double foundRatio = segment1.getRatioOfPoint(checkX, checkY);
    if (foundRatio > 0.000001) cout << foundRatio;
    cout << endl;

    cout << endl;

    double k = 2.0;
    Segment scaledSegment = segment1 * k;
    cout << "13) Произведение отрезка на число k = " << k << ": ";
    scaledSegment.print();
    cout << endl;
    cout << "Новая длина = " << scaledSegment.length() << endl;

    return 0;
}