/**
 * @file disjsets.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once
#include <vector>
namespace yzs
{
    class DisjSets
    {
        std::vector<int> s;

    public:
        DisjSets(int n) noexcept : s(n, -1)
        {
        }
        int find(int e)
        {
            if (s[e] < 0)
                return e;
            else
                return s[e] = find(s[e]);
        }
        #if 1
        //height
        void unite(int root1, int root2)
        {
            if (s[root2] < s[root1])
                s[root1] = root2;
            else
            {
                if (s[root1] == s[root2])
                    --s[root1]; //height
                s[root2] = root1;
            }
        }
        #else
        //size
        void unite(int root1, int root2)
        {
            if (s[root2] < s[root1])
            {
                s[root1] -= s[root2];
                s[root2] = root1;
            }
            else
            {
                s[root2] -= s[root1];
                s[root1] = root2;
            }
        }
        #endif
    };
} // namespace yzs
