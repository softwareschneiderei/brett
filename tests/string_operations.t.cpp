#include <brett/string_operations.hpp>
#include <catch2/catch.hpp>


TEST_CASE("Can split strings")
{
  std::string sample("This is;a sample: string.");
  SECTION("With a single char delimiter")
  {
    auto parts = brett::split(sample, ' ');
    REQUIRE(parts == std::vector<std::string>{"This", "is;a", "sample:", "string."});
  }
  SECTION("With a multi-char delimiter")
  {
    auto parts = brett::split(sample, "is");
    REQUIRE(parts == std::vector<std::string>{"Th", " ", ";a sample: string."});
  }
  SECTION("With multiple multi-char delimiters")
  {
    auto parts = brett::split(sample, {" ", ";", ": "});
    REQUIRE(parts == std::vector<std::string>{"This", "is", "a", "sample", "string."});
  }
}