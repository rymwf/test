/**
 * @file list.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <cstdlib>

namespace yzs
{

//TODO: merge, splice, reverse, sort, unique

template <class T>
struct ListNode
{
    T val;
    ListNode *next;
};

template <class T>
class List
{

    size_t _size{};
    ListNode<T> *_head{};

public:
    constexpr List() noexcept {}
    ~List() {
        clear();
    }

    constexpr T &at(size_t n)
    {
        ListNode<T> *node = _head;
        while (n-- > 0)
            node = node->next;
        return node->val;
    }
    constexpr T &operator[](size_t n)
    {
        return at(n);
    }
    constexpr bool empty()
    {
        return _head == nullptr;
    }
    constexpr size_t size()
    {
        return _size;
    }

    constexpr void push_back(const T &val)
    {
        insert(_size, val);
    }
    constexpr void insert(size_t pos, const T &val)
    {
        ListNode<T> *newnode = new ListNode<T>{val};
        if (pos == 0)
        {
            newnode->next = _head;
            _head = newnode;
        }
        else
        {
            ListNode<T> *temp = _head;
            while (--pos > 0)
                temp = temp->next;
            newnode->next = temp->next;
            temp->next = newnode;
        }
        _size++;
    }
    constexpr void erase(size_t pos)
    {
        ListNode<T> *node{};
        if (pos == 0)
        {
            node = _head->next;
            delete _head;
            _head = node;
        }
        else
        {
            node = _head;
            while (--pos > 0)
                node = node->next;
            ListNode<T> *temp = node->next;
            node->next = node->next->next;
            delete temp;
        }
        _size--;
    }
    constexpr void clear()
    {
        while (_head != nullptr)
        {
            ListNode<T> *temp = _head;
            _head = _head->next;
            delete temp;
        }
        _size = 0;
    }
};

} // namespace yzs
