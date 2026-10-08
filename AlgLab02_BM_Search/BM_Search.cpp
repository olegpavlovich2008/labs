#include <string>
#include <iostream>
#include <locale.h>

using namespace std;

int findFirst(const string& s, const string& p) 
{
    int N = s.size();
    int M = p.size();

    if (M == 0) 
        return -1;
    if (N < M) 
        return -1;

    int TAB[256];
    for (int idx = 0; idx < 256; idx = idx + 1) 
    {
        TAB[idx] = M;
    }
    for (int idx = 0; idx < M - 1; idx = idx + 1) 
    {
        unsigned char symbol = (unsigned char)p[idx];
        TAB[symbol] = M - 1 - idx;
    }

    int i = M - 1;

    while (i < N) 
    {
        int k = i;
        int j = M - 1;
        int count = 0;

        while (j >= 0) 
        {

            if (s[k] == p[j]) 
            {
                k = k - 1;
                j = j - 1;
                count = count + 1;
            }

            else 
            {
                break;
            }
        }

        if (j < 0) 
        {
            return i - M + 1;
        }
        else 
        {
            unsigned char badChar = (unsigned char)s[k];
            int step = TAB[badChar] - count;

            if (1 > step) 
            {
                step = 1;
            }

            i = i + step;
        }
    }

    return -1;
}

int main() {
    setlocale(LC_ALL, "RUS");

    string s = "std::move_iterator is an iterator adaptor";
    string p = "tor";

    int resultIndex = findFirst(s, p);

    cout << "Текст (s): " << s << endl;
    cout << "Подстрока (p): " << p << endl;
    cout << "Индекс первого вхождения: " << resultIndex << endl;

    return 0;
}