/**
 * @file topologicalSort.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>

using namespace std;
//only acylic
//topological sort
//bfs breadth first sort
std::vector<int> topologicalSort(std::vector<std::vector<int>> &graph, int n)
{
    vector<int> ret;
    vector<vector<int>> adjacentLists(n + 1);
    vector<int> indegreeTable(n + 1);

    for (auto &v : graph)
    {
        adjacentLists[v[0]].emplace_back(v[1]);
        indegreeTable[v[1]]++;
    }
    //start vertices are indegree0 ones
    for (int i = 1; i <= n; ++i)
    {
        if (indegreeTable[i] == 0)
        {
            ret.emplace_back(i);
        }
    }
    int len = ret.size();
    for (int i = 0; i < len; ++i)
    {
        for (auto e : adjacentLists[ret[i]])
        {
            if (indegreeTable[e] == 0)
                ret.emplace_back(e);
            else
                --indegreeTable[e];
        }
        len = ret.size();
    }
    return ret;
}
//dfs
std::vector<int> topologicalSort2(std::vector<std::vector<int>> &graph, int n)
{
    vector<vector<int>> adjacentLists(n + 1);
    for (auto &v : graph)
        adjacentLists[v[0]].emplace_back(v[1]);

    vector<int> ret;
    ret.reserve(n);
    vector<bool> visited(n + 1);
    static function<void(int)> dfs = [&](int index) {
        if (visited[index])
            return;
        for (auto &e : adjacentLists[index])
            dfs(e);
        visited[index] = true;
        ret.emplace_back(index);
    };
    for (int i = 1; i <= n; ++i)
        dfs(i);
    reverse(ret.begin(), ret.end());
    return ret;
}

int main()
{

    //acyclic
    std::vector<std::vector<int>> a{{1, 4, 1}, {1, 2, 2}, {2, 4, 3}, {2, 5, 10}, {1, 3, 4}, {3, 6, 5}, {4, 3, 2}, {4, 6, 8}, {4, 7, 4}, {5, 4, 1}, {5, 7, 6}, {7, 6, 1}};

    auto res = topologicalSort2(a, 7);

    for (auto &v : res)
    {
        cout << v << " ";
    }
}