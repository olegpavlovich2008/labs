#pragma once
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int** CreateMatr(int n, int lt, int rt, std::mt19937_64& gen) 
{
    int** matr = new int* [n];
    for (int i = 0; i < n; ++i) 
        matr[i] = new int[n];

    std::uniform_int_distribution<int> dist(lt, rt);
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            matr[i][j] = (i == j) ? 2147483647 : dist(gen);
        }
    }
    return matr;
}

void DeleteMatr(int** matr, int n) 
{
    for (int i = 0; i < n; ++i) delete[] matr[i];
    delete[] matr;
}

void Exact(int n, int** matr, int start, int& min_c, int& max_c, long long& t_exact, bool& f1, int* p_best) 
{
    int sz = n - 1;
    int* cities = new int[sz];
    int idx = 0;
    for (int i = 0; i < n; ++i) 
        if (i != start) 
            cities[idx++] = i;

    auto t1 = std::chrono::high_resolution_clock::now();
    bool has_next = true;

    do {
        int cost = 0, prev = start;
        bool ok = true;
        int* path = new int[n + 1];
        path[0] = start;

        for (int i = 0; i < sz; ++i) 
        {
            if (matr[prev][cities[i]] == 2147483647) { ok = false; break; }
            cost += matr[prev][cities[i]];
            prev = cities[i];
            path[i + 1] = prev;
        }

        if (ok && matr[prev][start] != 2147483647) 
        {
            cost += matr[prev][start];
            path[n] = start;
            f1 = true;

            if (cost < min_c) 
            {
                min_c = cost;
                for (int i = 0; i <= n; ++i) 
                    p_best[i] = path[i];
            }
            if (cost > max_c) max_c = cost;
        }
        delete[] path;


        int k = sz - 2;
        while (k >= 0 && cities[k] >= cities[k + 1]) 
            k--;
        if (k < 0) has_next = false;

        else 
        {
            int l = sz - 1;
            while (cities[l] <= cities[k]) l--;
            int tmp = cities[k]; cities[k] = cities[l]; cities[l] = tmp;
            int s = k + 1, e = sz - 1;
            while (s < e) 
            {
                int r = cities[s]; cities[s] = cities[e]; cities[e] = r;
                s++; e--;
            }
        }
    } while (has_next);

    auto t2 = std::chrono::high_resolution_clock::now();
    t_exact = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    delete[] cities;
}

void Heuristic(int n, int** matr, int start, int& heur_c, long long& t_heur, bool& f2, int* p_heur) 
{
    bool* visited = new bool[n]();
    p_heur[0] = start;
    visited[start] = true;
    int curr = start;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int step = 0; step < n - 1; ++step) 
    {
        int next = -1, min_e = 2147483647;
        for (int neighbor = 0; neighbor < n; ++neighbor) 
        {
            if (!visited[neighbor] && matr[curr][neighbor] < min_e) 
            {
                min_e = matr[curr][neighbor];
                next = neighbor;
            }
        }

        if (next == -1) { f2 = false; break; }
        p_heur[step + 1] = next;
        visited[next] = true;
        heur_c += min_e;
        curr = next;
    }

    if (f2 && matr[curr][start] != 2147483647) 
    {
        heur_c += matr[curr][start];
        p_heur[n] = start;
    }
    else f2 = false;

    auto t2 = std::chrono::high_resolution_clock::now();
    t_heur = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    delete[] visited;
}