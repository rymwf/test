#include <cstdio>
#include <vector>
#include <functional>

//two way merge sort
void mergeSort(std::vector<int> &arr)
{
    auto merge = [](std::vector<int> &a, int l, int p, int r) {
        std::vector<int> temp;
        temp.reserve(r - l + 1);
        int p1 = l, p2 = p + 1;
        while (p1 <= p && p2 <= r)
        {
            if(a[p1]<a[p2]){
                temp.emplace_back(a[p1]);
                p1++;
            }else{
                temp.emplace_back(a[p2]);
                p2++;
            }
        }
        if (p1 > p)
        {
            for (; p2 <= r; p2++)
                temp.emplace_back(a[p2]);
        }
        else if (p2 > r)
        {
            for (; p1 <= p; p1++)
                temp.emplace_back(a[p1]);
        }
        for (int i = l; i <= r; ++i)
        {
            a[i] = temp[i - l];
        }
    };
    std::function<void(int, int)> f = [&](int l, int r) {
        if (l >= r)
            return;
        int p = (l + r) / 2;
        f(l, p);
        f(p + 1, r);
        merge(arr, l, p, r);
    };
    f(0, arr.size() - 1);
}