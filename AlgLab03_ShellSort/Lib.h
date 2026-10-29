#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintArr(const vector<int>& a)
{
    for (int i = 0; i < a.size(); ++i)
    {
        int num = a[i];
        cout << num << " ";
    }
    cout << "\n";
}

void ShellSort(vector<int>& a, const vector<int>& h)
{
    int t = h.size() - 1;
    int n = a.size();

    for (int i = 0; i <= t; ++i)
    {
        int s = h[i];

        for (int b = 0; b < s; ++b)
        {
            int j = b + s;

            while (j < n)
            {
                int x = a[j];
                int k = j - s;

                while (k >= 0 && a[k] > x)
                {
                    a[k + s] = a[k];
                    k = k - s;
                }

                a[k + s] = x;
                j = j + s;
            }
        }
    }
}

bool Sorted(const vector<int>& a)
{
    for (int i = 1; i < a.size(); ++i)
    {
        if (a[i - 1] > a[i])
        {
            return false;
        }
    }
    return true;
}

vector<int> GetShell(int n)
{
    vector<int> h;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        h.push_back(gap);
    }
    if (h.empty() || h.back() != 1)
    {
        h.push_back(1);
    }
    return h;
}

vector<int> GetKnuth(int n)
{
    vector<int> h;
    int gap = 1;
    while (gap < n)
    {
        h.push_back(gap);
        gap = 3 * gap + 1;
    }
    reverse(h.begin(), h.end());
    return h;
}

vector<int> GetSedgewick(int n)
{
    vector<int> h;
    int j = 0;
    while (true)
    {
        int gap = 0;
        if (j % 2 == 0)
        {
            gap = 9 * (1 << j) - 9 * (1 << (j / 2)) + 1;
        }
        else
        {
            gap = 8 * (1 << j) - 6 * (1 << ((j + 1) / 2)) + 1;
        }

        if (gap >= n)
        {
            break;
        }

        h.push_back(gap);
        j++;
    }

    if (h.empty())
    {
        h.push_back(1);
    }
    else
    {
        reverse(h.begin(), h.end());
    }
    return h;
}