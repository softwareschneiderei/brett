#include "brett/aligned_allocator.hpp"

std::uint8_t* brett::allocate_aligned(std::size_t n, std::size_t N)
{
  std::size_t const alignment = std::max(alignof(ptrdiff_t), N);
  std::size_t const object_size = sizeof(ptrdiff_t) + N * n;
  std::size_t const buffer_size = object_size + alignment;

  auto const block = reinterpret_cast<char*>(std::malloc(buffer_size));
  if (block == nullptr)
  {
    throw std::bad_alloc{};
  }

  void* storage = (block) + sizeof(ptrdiff_t);
  size_t shift = buffer_size;

  char* const body = reinterpret_cast<char*>(std::align(alignment, object_size, storage, shift));
  char* const offset = body - sizeof(ptrdiff_t);

  *reinterpret_cast<ptrdiff_t*>(offset) = body - block;

  return reinterpret_cast<std::uint8_t*>(body);
}

void brett::deallocate_aligned(std::uint8_t* p)
{
  char const* header = reinterpret_cast<char*>(p) - sizeof(ptrdiff_t);
  auto offset = *reinterpret_cast<ptrdiff_t const*>(header);
  void* const block = reinterpret_cast<char*>(p) - offset;
  std::free(block);
}
