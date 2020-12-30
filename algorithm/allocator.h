/**
 * @file allocator.h
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
template <class T>
struct Allocator
{
    constexpr Allocator() noexcept {}
    constexpr Allocator(const Allocator &other) noexcept {}
    template <class U>
    constexpr Allocator(const Allocator<U> &other) noexcept {}

    //    constexpr ~Allocator();
    ~Allocator() {}

    [[nodiscard]] constexpr T *allocate(std::size_t n)
    {
        return new T[n];
    }
    constexpr void deallocate(T *p, std::size_t n)
    {
        delete[] p;
    }
};

} // namespace yzs
