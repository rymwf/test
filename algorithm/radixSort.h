#pragma once
#include <vector>
#include <string>

//radix must be power of 2 or 10
void radixSort(std::vector<int> &arr, int radix = 10)
{
    //could find max value first
    if (radix!= 10)
    {
        int r = radix;
        int n = -1;
        while (r)
        {
            r>>= 1;
            n++;
        }
        bool flag = true;
        int k = 0;
        std::vector<std::vector<int>> temp;
        while (flag)
        {

            temp.clear();
            temp.resize(radix);
            flag = false;
            for (auto i : arr)
            {
                int a = (i >> (k * n)) & (radix - 1);
                if (a > 0)
                    flag = true;
                temp[a].emplace_back(i);
            }
            int i = 0;
            for (auto v : temp)
                for (auto e : v)
                {
                    arr[i] = e;
                    i++;
                }
            k++;
        }
        return;
    }
    std::vector<std::vector<int>> temp;
    int divider = 1;
    bool flag = true;
    while (flag)
    {
        temp.clear();
        temp.resize(radix);
        flag = false;
        for (int i : arr)
        {
            int a = (i / divider) % radix;
            if (a > 0)
                flag = true;
            temp[a].emplace_back(i);
        }
        int i = 0;
        for (auto v : temp)
            for (auto e : v)
            {
                arr[i] = e;
                i++;
            }
        divider *= 10;
    }
}
