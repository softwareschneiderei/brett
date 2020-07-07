#include <catch2/catch.hpp>
#include <brett/discrete_curve.hpp>

TEST_CASE("Can create a small gauss kernel")
{
  auto kernel = brett::gauss_kernel(3, 1.0);

  std::vector<double> const reference = {
    0.0044330481752437451,
    0.054005582622414484,
    0.2420362293761143,
    0.39905027965245488,
    0.2420362293761143,
    0.054005582622414484,
    0.0044330481752437451,
  };

  REQUIRE(kernel == reference);
}
