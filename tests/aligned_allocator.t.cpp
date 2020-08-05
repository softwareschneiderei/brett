#include <catch2/catch.hpp>
#include <brett/aligned_allocator.hpp>


TEST_CASE("Sampling 8-byte aligned allocations yields zeros in the last 3 bits of the addresses")
{
  std::vector<std::uint8_t*> ptrs;

  for (std::size_t i = 0; i < 100; ++i)
  {
    auto address = brett::allocate_aligned(sizeof(double)*(72 + i), 8);
    auto address_as_int = reinterpret_cast<std::uint64_t>(address);
    REQUIRE((address_as_int & 7) == 0);
    ptrs.push_back(address);
  }

  for (auto each : ptrs)
  {
    brett::deallocate_aligned(each);
  }
}
