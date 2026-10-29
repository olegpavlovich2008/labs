#pragma once

#include <iostream>
#include <vector>

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