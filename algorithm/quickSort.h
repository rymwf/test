#pragma once
#include <cstdio>
#include <functional>
#include <vector>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(std::vector<int>& arr)
{
    static std::function<void(std::vector<int> &, int, int)> f = [](std::vector<int> &arr, int l, int r) {
        if (l >= r)
            return;
        int p = (l + r) / 2;
        swap(arr[p], arr[r]);
        int p1 = l, p2 = l;
        for (; p2 < r; p2++)
        {
            if (arr[p2] < arr[r])
            {
                swap(arr[p2], arr[p1]);
                p1++;
            }
        }
        swap(arr[r], arr[p1]);
        f(arr, l, p1 - 1);
        f(arr, p1 + 1, r);
    };
    f(arr, 0, arr.size() - 1);
}

void quickSort2(std::vector<int>& arr)
{
    static std::function<void(std::vector<int> &, int, int)> f = [](std::vector<int> &arr, int l, int r) {
        if (l >= r)
            return;
        int p1 = l, p2 = l;
        for (; p2 < r; p2++)
        {
            if (arr[p2] < arr[r])
            {
                swap(arr[p2], arr[p1]);
                p1++;
            }
        }
        f(arr, l, p1 - 1);
        f(arr, p1 + 1, r);
    };
    f(arr, 0, arr.size() - 1);
}