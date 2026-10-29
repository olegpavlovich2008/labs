#include <iostream>
#include <vector>
#include <locale.h>
#include <random>
#include <chrono>
#include "Lib.h"

using namespace std;
using namespace std::chrono;

int main()
{
    setlocale(LC_ALL, "RUS");

    FILE* file = nullptr;
    fopen_s(&file, "Results.txt", "w");

    cout << "=== СТАНДАРТНАЯ СОРТИРОВКА ШЕЛЛА ===\n";
    if (file) fprintf(file, "=== СТАНДАРТНАЯ СОРТИРОВКА ШЕЛЛА ===\n");

    vector<int> arr = { 45, -7, 12, 89, 0, 3, -15, 21, 64, 7, 33, 19, 1, -5, 42 };
    vector<int> h = { 7, 3, 1 };

    cout << "Исходный массив: ";
    PrintArr(arr);

    if (file)
    {
        fprintf(file, "Исходный массив: ");
        for (size_t i = 0; i < arr.size(); ++i)
        {
            fprintf(file, "%d ", arr[i]);
        }
        fprintf(file, "\n");
    }

    ShellSort(arr, h);

    cout << "Отсортированный массив: ";
    PrintArr(arr);

    if (file)
    {
        fprintf(file, "Отсортированный массив: ");
        for (size_t i = 0; i < arr.size(); ++i)
        {
            fprintf(file, "%d ", arr[i]);
        }
        fprintf(file, "\n");
    }

    if (Sorted(arr))
    {
        cout << "Массив упорядочен.\n";
        if (file) fprintf(file, "Массив упорядочен.\n");
    }
    else
    {
        cout << "Массив неупорядочен.\n";
        if (file) fprintf(file, "Массив неупорядочен.\n");
    }
    cout << "======================================================\n\n";
    if (file) fprintf(file, "======================================================\n\n");

    cout << "=== ТЕСТИРОВАНИЕ РАЗЛИЧНЫХ АЛГОРИТМОВ ВЫБОРА ДЛИНЫ ПРОМЕЖУТКОВ ===\n";
    if (file) fprintf(file, "=== ТЕСТИРОВАНИЕ РАЗЛИЧНЫХ АЛГОРИТМОВ ВЫБОРА ДЛИНЫ ПРОМЕЖУТКОВ ===\n");

    random_device rd;
    mt19937 gen(rd());

    int sizes[] = { 10000, 100000, 1000000 };
    int minVal[] = { -10, -1000, -100000 };
    int maxVal[] = { 10, 1000, 100000 };

    cout << "Размер\tДиапазон\tЗапуск\tШелл\tКнут\tСэджвик\n";
    cout << "------------------------------------------------------------------------------------\n";
    if (file)
    {
        fprintf(file, "Размер\tДиапазон\tЗапуск\tШелл\tКнут\tСэджвик\n");
        fprintf(file, "------------------------------------------------------------------------------------\n");
    }

    for (int s = 0; s < 3; ++s)
    {
        int currentSize = sizes[s];

        for (int r = 0; r < 3; ++r)
        {
            int currentMin = minVal[r];
            int currentMax = maxVal[r];

            vector<int> original_array(currentSize);
            uniform_int_distribution<int> dist(currentMin, currentMax);
            for (int i = 0; i < currentSize; ++i)
            {
                original_array[i] = dist(gen);
            }

            vector<int> gapsShell = GetShell(currentSize);
            vector<int> gapsKnuth = GetKnuth(currentSize);
            vector<int> gapsSedgewick = GetSedgewick(currentSize);

            double sum_time_shell = 0;
            double sum_time_knuth = 0;
            double sum_time_sedgewick = 0;

            for (int run = 1; run <= 3; ++run)
            {
                vector<int> t_arr;


                t_arr = original_array;
                auto start = steady_clock::now();
                ShellSort(t_arr, gapsShell);
                auto end = steady_clock::now();
                int run_time_shell = (int)duration_cast<milliseconds>(end - start).count();
                sum_time_shell += run_time_shell;


                t_arr = original_array;
                start = steady_clock::now();
                ShellSort(t_arr, gapsKnuth);
                end = steady_clock::now();
                int run_time_knuth = (int)duration_cast<milliseconds>(end - start).count();
                sum_time_knuth += run_time_knuth;


                t_arr = original_array;
                start = steady_clock::now();
                ShellSort(t_arr, gapsSedgewick);
                end = steady_clock::now();
                int run_time_sedgewick = (int)duration_cast<milliseconds>(end - start).count();
                sum_time_sedgewick += run_time_sedgewick;


                cout << currentSize << "\t[" << currentMin << ", " << currentMax << "]\t№" << run << "\t"
                    << run_time_shell << " мс\t\t"
                    << run_time_knuth << " мс\t\t"
                    << run_time_sedgewick << " мс\n";

                if (file) 
                {
                    fprintf(file, "%d\t[%d, %d]\t№%d\t%d мс\t\t%d мс\t\t%d мс\n",
                        currentSize, currentMin, currentMax, run,
                        run_time_shell, run_time_knuth, run_time_sedgewick);
                }
            }

            int avg_shell = (int)(sum_time_shell / 3.0);
            int avg_knuth = (int)(sum_time_knuth / 3.0);
            int avg_sedgewick = (int)(sum_time_sedgewick / 3.0);


            cout << currentSize << "\t[" << currentMin << ", " << currentMax << "]\tСр. знач.\t"
                << avg_shell << " мс\t\t"
                << avg_knuth << " мс\t\t"
                << avg_sedgewick << " мс\n";

            if (file) 
            {
                fprintf(file, "%d\t[%d, %d]\tСр. знач.\t%d мс\t\t%d мс\t\t%d мс\n",
                    currentSize, currentMin, currentMax,
                    avg_shell, avg_knuth, avg_sedgewick);
            }

            cout << "------------------------------------------------------------------------------------\n";
            if (file) fprintf(file, "------------------------------------------------------------------------------------\n");
        }
    }

    if (file)
    {
        fclose(file);
    }

    return 0;
}