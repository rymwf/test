#include "BinarySearchTree.h"
#include "avltree.h"
#include "graph.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using namespace std;

//directed unweighted
std::vector<int> shortestPathUnweighted(std::vector<std::vector<int>> &graph, int n, int start, int end)
{
    vector<vector<int>> adjacentLists(n + 1);
    for (auto &v : graph)
        adjacentLists[v[0]].emplace_back(v[1]);
    vector<int> ret;
    vector<pair<int, int>> prev(n + 1, {0, INT_MAX});
    queue<int> q;
    q.emplace(start);
    int weight = 0;
    prev[start] = {0, 0};
    while (!q.empty())
    {
        weight++;
        auto a = q.front();
        q.pop();
        for (auto &e : adjacentLists[a])
        {
            if (prev[e].second > weight)
            {
                prev[e] = {a, weight};
                q.emplace(e);
            }
        }
    }
    ret.emplace_back(end);
    while (prev[end].first != start)
    {
        end = prev[end].first;
        ret.emplace_back(end);
    }
    ret.emplace_back(start);
    reverse(ret.begin(), ret.end());
    return ret;
}
std::vector<int> shortestPathWeighted(std::vector<std::vector<int>> &graph, int n, int start, int end)
{
    vector<vector<pair<int, int>>> adjacentLists(n + 1);
    for (auto &v : graph)
        adjacentLists[v[0]].emplace_back(v[1], v[2]);
    vector<int> ret;
    vector<pair<int, int>> prev(n + 1, {0, INT_MAX});
    queue<int> q;
    q.emplace(start);
    int weight = 0;
    prev[start] = {0, 0};
    while (!q.empty())
    {
        auto a = q.front();
        q.pop();
        for (auto &e : adjacentLists[a])
        {
            if (prev[e.first].second > weight + e.second)
            {
                prev[e.first] = {a, weight + e.second};
                q.emplace(e.first);
            }
        }
    }
    ret.emplace_back(end);
    while (prev[end].first != start)
    {
        end = prev[end].first;
        ret.emplace_back(end);
    }
    ret.emplace_back(start);
    reverse(ret.begin(), ret.end());
    return ret;
}

int main()
{
    //    yzs::AvlTree<int> avltree;
    //    //yzs::BinarySearchTree<int> avltree;
    //    std::vector<int> a = {4, 5, 6, 2, 3, 1, 4, 1, 2, 3, 4, 5, 3, 8, 4, 2, 9, 64, 2, 3, 411, 22, 33, 45, 76};
    //    for(auto i:a)
    //        avltree.insert(i);
    //    avltree.printTree(std::cout);

    //acyclic
    //std::vector<std::vector<int>> a{{1, 4, 1}, {1, 2, 2}, {2, 4, 3}, {2, 5, 10}, {1, 3, 4}, {3, 6, 5}, {4, 3, 2}, {4, 6, 8}, {4, 7, 4}, {5, 4, 1}, {5, 7, 6}, {7, 6, 1}};
    //cyclic
    std::vector<std::vector<int>> a{{1, 4, 1}, {1, 2, 2}, {2, 4, 3}, {2, 5, 10}, {3, 1, 4}, {3, 6, 5}, {4, 3, 2}, {4, 5, 2}, {4, 6, 8}, {4, 7, 4}, {5, 7, 1}, {7, 6, 1}};
    //cyclic with negative-cost cycle
    //std::vector<std::vector<int>> a{{1, 4, 1}, {1, 2, 2}, {2, 4, 3}, {2, 5, -10}, {3, 1, 4}, {3, 6, 5}, {4, 3, 2}, {4, 5, 2}, {4, 6, 8}, {4, 7, 4}, {5, 7, 6}, {7, 6, 1}};

    //auto res = shortestPathUnweighted(a, 7, 3, 7);
    auto res = shortestPathWeighted(a, 7, 3, 7);

    for (auto &v : res)
    {
        cout << v << " ";
    }
}
