#include <cstdio>
#include <functional>
#include <vector>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int quickSort(std::vector<int>& arr)
{
    int count=0;
    static std::function<void(std::vector<int> &, int, int)> f = [&count](std::vector<int> &arr, int l, int r) {
        if (l >= r)
            return;
        count++;
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
    return count;
}

int quickSort2(std::vector<int>& arr)
{
    int count=0;
    static std::function<void(std::vector<int> &, int, int)> f = [&count](std::vector<int> &arr, int l, int r) {
        if (l >= r)
            return;
        count++;
        int p = r;
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
    return count;
}
int main()
{
    std::vector<int> a = {3, 4, 5, 6, 2, 2, 3, 34, 4, 1, 21, 1, 2, 23, 213, 43445, 4, 6, 4, 6, 67, 65, 3};
    auto a2=a;
    for (int i = 0; i < a.size(); ++i)
        printf("%d ", a[i]);
    printf("\n");
    int count=quickSort(a);

    for (int i = 0; i < a.size(); ++i)
        printf("%d ", a[i]);
    printf("count: %d\n",count);

    count=quickSort2(a2);
    for (int i = 0; i < a2.size(); ++i)
        printf("%d ", a2[i]);
    printf("count: %d\n",count);
}
