#pragma once
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <memory>

namespace brett
{
std::uint8_t* allocate_aligned(std::size_t n, std::size_t alignment);
void deallocate_aligned(std::uint8_t* p);

template <std::size_t ALIGNMENT, typename T = std::uint8_t>
class aligned_allocator
{
public:
  using pointer = T*;
  using size_type = size_t;
  using value_type = T;

  aligned_allocator() = default;

  template <class U>
  aligned_allocator(aligned_allocator<ALIGNMENT, U> const&)
  {
  }

  pointer allocate(size_type n)
  {
    return reinterpret_cast<pointer>(allocate_aligned(n, ALIGNMENT));
  }

  void deallocate(pointer p, size_type)
  {
    return deallocate_aligned(reinterpret_cast<std::uint8_t*>(p));
  }

  template <class U>
  struct rebind
  {
    using other = aligned_allocator<ALIGNMENT, U>;
  };
};
}