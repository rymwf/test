/**
 * @file priorityqueue.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include "vector.h"

//TODO: add compare function
namespace yzs
{

template <class _T, class _Container = Vector<_T>>
class PriorityQueue
{
    _Container _container;

    constexpr size_t findpos(const _T &val)
    {
        size_t l = 0, r = _container.size();
        size_t mid;
        while (l < r)
        {
            mid = (l + r) >> 1;
            if (_container[mid] > val)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        return r;
    }

public:
    constexpr PriorityQueue() noexcept {}

    ~PriorityQueue() {}

    constexpr _T &top()
    {
        return _container.back();
    }
    constexpr bool empty()
    {
        return _container.empty();
    }
    constexpr size_t size()
    {
        return _container.size();
    }
    constexpr void push(const _T &val)
    {
        if (empty())
        {
            _container.push_back(val);
        }
        else
        {
            _container.insert(findpos(val), val);
        }
    }
    constexpr void pop()
    {
        _container.pop_back();
    }
};

} // namespace yzs