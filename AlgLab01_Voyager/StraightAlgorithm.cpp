#include <iostream>
#include <chrono>
#include <random>
#include <locale.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    int n, start_city, lt, rt;
    cout << "Введите кол-во городов (2 >= n <= 15): ";
    cin >> n;
    cout << "Введите минимальную стоимость: ";
    cin >> lt;
    cout << "Введите максимальную стоимость: ";
    cin >> rt;
    cout << "Введите стартовый город: ";
    cin >> start_city;

    if (n > 15 || n < 2)
    {
        cout << "Ошибка: Некорректное значение n." << endl;
        return 1;
    }

    int matrix[15][15];

    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(lt, rt);

    cout << "\nМатрица стоимостей:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 2147483647;
                cout << "-\t";
            }
            else
            {
                matrix[i][j] = distribution(generator);
                cout << matrix[i][j] << "\t";
            }
        }
        cout << endl;
    }

    int perm_cities[15];
    int idx = 0;
    for (int i = 0; i < n; ++i)
    {
        if (i != start_city)
        {
            perm_cities[idx++] = i;
        }
    }

    int size_perm = n - 1;
    int min_cost = 2147483647;
    int max_cost = -1;
    int best_path[16];
    int worst_path[16];

    std::chrono::high_resolution_clock::time_point timeBegin = std::chrono::high_resolution_clock::now();

    bool has_next_permutation = true;
    do {
        int current_cost = 0;
        int prev_city = start_city;
        bool possible_path = true;

        int current_path[16];
        current_path[0] = start_city;

        for (int i = 0; i < size_perm; ++i)
        {
            if (matrix[prev_city][perm_cities[i]] == 2147483647) 
            {
                possible_path = false;
                break;
            }
            current_cost += matrix[prev_city][perm_cities[i]];
            prev_city = perm_cities[i];
            current_path[i + 1] = prev_city;
        }

        if (possible_path && matrix[prev_city][start_city] != 2147483647) 
        {
            current_cost += matrix[prev_city][start_city];
            current_path[n] = start_city;

            if (current_cost < min_cost)
            {
                min_cost = current_cost;
                for (int i = 0; i <= n; ++i) best_path[i] = current_path[i];
            }

            if (current_cost > max_cost)
            {
                max_cost = current_cost;
                for (int i = 0; i <= n; ++i) worst_path[i] = current_path[i];
            }
        }


        int k = size_perm - 2;
        while (k >= 0 && perm_cities[k] >= perm_cities[k + 1]) 
            k--;

        if (k < 0) has_next_permutation = false;
        else 
        {
            int l = size_perm - 1;

            while (perm_cities[l] <= perm_cities[k]) 
                l--;

            std::swap(perm_cities[k], perm_cities[l]);
            int start = k + 1;
            int end = size_perm - 1;

            while (start < end) 
            {
                std::swap(perm_cities[start], perm_cities[end]);
                start++;
                end--;
            }
        }
    } while (has_next_permutation);

    std::chrono::high_resolution_clock::time_point exactEnd = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds interval = std::chrono::duration_cast<std::chrono::milliseconds>(exactEnd - timeBegin);


    //ЭВРИСТИКА

    int heur_path[16];
    int heur_cost = 0;
    bool visited_cities[15] = {};

    std::chrono::high_resolution_clock::time_point heurBegin = std::chrono::high_resolution_clock::now();

    heur_path[0] = start_city;
    visited_cities[start_city] = true;
    int current_city = start_city;
    bool heur_ok = true;

    for (int step = 0; step < n - 1; ++step) 
    {
        int next_city = -1;
        int min_edge = 2147483647;

        for (int neighbor = 0; neighbor < n; ++neighbor) 
        {
            if (!visited_cities[neighbor] && matrix[current_city][neighbor] < min_edge) 
            {
                min_edge = matrix[current_city][neighbor];
                next_city = neighbor;
            }
        }

        if (next_city == -1) 
        {
            heur_ok = false;
            break;
        }

        heur_path[step + 1] = next_city;
        visited_cities[next_city] = true;
        heur_cost += min_edge;
        current_city = next_city;
    }

    if (heur_ok && matrix[current_city][start_city] != 2147483647) 
    {
        heur_cost += matrix[current_city][start_city];
        heur_path[n] = start_city;
    }
    else 
    {
        heur_ok = false;
    }


    std::chrono::high_resolution_clock::time_point heurEnd = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds heurInterval = std::chrono::duration_cast<std::chrono::microseconds>(heurEnd - heurBegin);



    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;

    cout << "Размерность матрицы: " << n << "x" << n << " | Разброс стоимостей: [" << lt << ".." << rt << "]" << endl;

    cout << "--- ТОЧНЫЙ АЛГОРИТМ ---" << endl;
    cout << "Наилучший путь: ";
    for (int i = 0; i <= n; ++i) cout << best_path[i] + 1 << (i == n ? "" : " -> ");
    cout << " | Стоимость: " << min_cost << endl;
    cout << "Наихудший путь: ";
    for (int i = 0; i <= n; ++i) 
        cout << worst_path[i] + 1 << (i == n ? "" : " -> ");
    cout << " | Стоимость: " << max_cost << endl;
    cout << "Время: " << interval.count() / 1000.0 << " с." << endl;


    cout << "--- ЭВРИСТИКА ---" << endl;
    if (!heur_ok) 
    {
        cout << "Маршрут не найден!" << endl;
    }
    else
    {
        cout << "Найденный эвристический путь: ";
        for (int i = 0; i <= n; ++i)
            cout << heur_path[i] + 1 << (i == n ? "" : " -> ");
        cout << " | Стоимость: " << heur_cost << endl;
        cout << "Время работы эвристики: " << heurInterval.count() << " мкс." << endl;
    }

    double quality = 100.0;
    if (max_cost != min_cost) 
    {
        quality = (double)(max_cost - heur_cost) / (max_cost - min_cost) * 100.0;
    }
    cout << "Качество решения: " << quality << " %." << endl;

    return 0;
}