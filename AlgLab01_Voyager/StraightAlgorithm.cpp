#include <iostream>
#include <chrono>
#include <random>
#include <locale.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    int n, start_city;
    cout << "Введите кол-во городов (2 >= n <= 15): ";
    cin >> n;
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
    std::uniform_int_distribution<int> distribution(1, 99);

    cout << "\nМатрица стоимостей:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = distribution(generator);
            }
            cout << matrix[i][j] << "\t";
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
    int best_path[16];



    std::chrono::high_resolution_clock::time_point timeBegin = std::chrono::high_resolution_clock::now();



    bool has_next_permutation = true;
    do {
        int current_cost = 0;
        int prev_city = start_city;

        int current_path[16];
        current_path[0] = start_city;

        for (int i = 0; i < size_perm; ++i)
        {
            current_cost += matrix[prev_city][perm_cities[i]];
            prev_city = perm_cities[i];
            current_path[i + 1] = prev_city;
        }
        current_cost += matrix[prev_city][start_city];
        current_path[n] = start_city;

        if (current_cost < min_cost)
        {
            min_cost = current_cost;
            for (int i = 0; i <= n; ++i)
            {
                best_path[i] = current_path[i];
            }
        }

        int k = size_perm - 2;
        while (k >= 0 && perm_cities[k] >= perm_cities[k + 1])
        {
            k--;
        }

        if (k < 0)
        {
            has_next_permutation = false;
        }
        else
        {
            int l = size_perm - 1;

            while (perm_cities[l] <= perm_cities[k])
            {
                l--;
            }
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



    cout << "\n=== РЕЗУЛЬТАТ ===" << endl;
    cout << "Минимальная стоимость: " << min_cost << endl;
    cout << "Оптимальный маршрут: ";
    for (int i = 0; i <= n; ++i) {
        cout << best_path[i] << (i == n ? "" : " - ");
    }
    cout << endl;
    cout << "Время расчёта: " << interval.count() / 1000.0 << " с." << endl;

    return 0;
}
