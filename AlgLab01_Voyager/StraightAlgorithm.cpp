#include <iostream>
#include <locale.h>
#include "Lib.h"

using namespace std;

void runTest(int n, int global_lt, int global_rt, int test_num = 1) 
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> bound_dist(global_lt, global_rt);

    int lt = bound_dist(gen), rt = bound_dist(gen);
    if (lt > rt) 
    { 
        int t = lt; 
        lt = rt; 
        rt = t; 
    }

    int start_city = 0;
    int** matr = CreateMatr(n, lt, rt, gen);

    if (n <= 10) 
        cout << "  [Тест №" << test_num << "] Границы стоимостей: [" << lt << "-" << rt << "]" << endl;
    else 
        cout << "=== ТЕСТ ДЛЯ РАЗМЕРНОСТИ N = " << n << " ===\nГраницы стоимостей: [" << lt << "-" << rt << "]" << endl;

    int min_c = 2147483647;
    int max_c = -1;
    int heur_c = 0;
    long long t_exact = 0;
    long long t_heur = 0;
    bool f1 = false;
    bool f2 = true;
    int* p_best = new int[n + 1]();
    int* p_heur = new int[n + 1]();

    if (n <= 10) 
        Exact(n, matr, start_city, min_c, max_c, t_exact, f1, p_best);
        Heuristic(n, matr, start_city, heur_c, t_heur, f2, p_heur);

    if (n <= 10) 
    {
        if (f1) 
        {
            cout << "Точный алгоритм: Лучший = " << min_c << " | Худший = " << max_c << " | Время: " << t_exact << " мс." << endl;
            cout << "Лучший путь:  "; for (int i = 0; i <= n; ++i) cout << p_best[i] + 1 << (i == n ? "" : " -> "); cout << endl;
        }
        if (f2) 
        {
            cout << "Эвристика: Стоимость = " << heur_c << " | Время: " << t_heur << " мкс." << endl;
            cout << "Эврист. путь: "; for (int i = 0; i <= n; ++i) cout << p_heur[i] + 1 << (i == n ? "" : " -> "); cout << endl;
        }
        if (f1 && f2 && max_c != min_c)
            cout << "Качество эвристики: " << (double)(max_c - heur_c) / (max_c - min_c) * 100.0 << " %" << endl;
    }
    else 
    {
        if (f2) 
            cout << "Эвристика: Стоимость = " << heur_c << " | Время работы: " << t_heur << " мкс." << endl;
            cout << "Качество эвристики: Невозможно рассчитать (точный метод неприменим)." << endl;
    }
    cout << endl;


    DeleteMatr(matr, n);
    delete[] p_best;
    delete[] p_heur;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int global_lt, global_rt;
    cout << "Введите мин. и макс. границы стоимостей (через пробел): ";
    cin >> global_lt >> global_rt;
    cout << endl;

    int small_sizes[] = { 4, 6, 8, 10 };
    for (int i = 0; i < 4; ++i) 
    {
        int size = small_sizes[i];
        cout << "=========================================\nРАЗМЕРНОСТЬ МАТРИЦЫ: " << size << "x" << size << "\n=========================================" << endl;
        for (int t = 1; t <= 4; ++t) runTest(size, global_lt, global_rt, t);
    }

    runTest(100, global_lt, global_rt);
    runTest(1000, global_lt, global_rt);
    return 0;
}