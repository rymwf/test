/**
 * @file vector.h
 * @author yangzs
 * @brief 
 * @version 0.1
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include "allocator.h"

#define DEFAULT_INITIALIZE_VALUE 0

namespace yzs
{

template <class _T, class _Alloc = yzs::Allocator<_T>>
class Vector
{
    size_t size_{};
    size_t capacity_{};
    _T *p_{};
    _Alloc alloc_{};

    size_t newcapacity() { return 2 * (capacity_ + 1); }

public:
    constexpr Vector() noexcept {}
    //constexpr Vector() noexcept(noexcept(Allocator())) {}
    //constexpr explicit Vector(const Allocator &alloc) noexcept;

    //constexpr Vector(size_t count, const _T &val, const Allocator &alloc = Allocator()) noexcept;
    //constexpr explicit Vector(size_t count, const Allocator &alloc = Allocator()) noexcept;

    //constexpr Vector(const Vector &other) noexcept;
    //constexpr Vector(const Vector &other,const Allocator& alloc) noexcept;

    //constexpr Vector(Vector &&other) noexcept;
    //constexpr Vector(Vector &&other, const Allocator &alloc) noexcept;

    ~Vector()
    {
        alloc_.deallocate(p_, capacity_);
    }

    constexpr _T &at(size_t n) { return p_[n]; }
    constexpr _T &operator[](size_t n) { return p_[n]; }

    constexpr _T &front() { return p_[0]; }
    constexpr _T &back() { return p_[size_ - 1]; }

    constexpr bool empty() { return size_ == 0; }

    constexpr size_t size()
    {
        return size_;
    }
    size_t max_size() { return capacity_; }
    constexpr void reserve(size_t n)
    {
        if (n <= capacity_)
            return;
        _T *temp = alloc_.allocate(n);
        for (size_t i = 0; i < size_; ++i)
            temp[i] = p_[i];
        alloc_.deallocate(p_, capacity_);
        p_ = temp;
        capacity_ = n;
    }
    constexpr size_t capacity() { return capacity_; }

    constexpr void clear()
    {
        alloc_.deallocate(p_, capacity_);
        p_ = nullptr;
        capacity_ = 0;
        size_ = 0;
    }
    
    constexpr void assign(size_t count,const _T& val){
        resize(count);
        while(count-->0)
            p_[count]=val;
    }

    constexpr void insert(size_t pos, const _T &val)
    {
        if (size_ == capacity_)
            reserve(newcapacity());
        size_t i = size_;
        while (i != pos)
        {
            p_[i] = p_[i-1];
            i-=1;
        }
        p_[pos] = val;
        size_++;
    }
    constexpr void erase(size_t pos)
    {
        size_--;
        while (pos < size_)
            p_[pos] = p_[++pos];
    }
    constexpr void push_back(const _T &val)
    {
        if (size_ == capacity_)
            reserve(newcapacity());
        p_[size_] = val;
        size_++;
    }
    constexpr void pop_back()
    {
        size_--;
    }
    constexpr void resize(size_t n)
    {
        reserve(n);
        while (size_ < n)
            p_[size_++] = DEFAULT_INITIALIZE_VALUE;
        size_ = n;
    }
    constexpr void swap(size_t srcpos, size_t dstpos)
    {
        int a = p_[dstpos];
        p_[dstpos] = p_[srcpos];
        p_[srcpos] = a;
    }
};

} // namespace yzs