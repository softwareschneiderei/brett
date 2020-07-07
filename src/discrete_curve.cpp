#include <brett/discrete_curve.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>


namespace
{
using namespace brett;
constexpr double PI = 3.141592653589793238463;
}  // namespace


discrete_curve brett::gauss(
  discrete_curve const& data, double sigma)
{
  auto constexpr STANDARD_DEVIATIONS_IN_RADIUS = 3.0;
  auto kernel = gauss_kernel(std::ceil(STANDARD_DEVIATIONS_IN_RADIUS*sigma), sigma);

  return convolve(data, kernel);
}


discrete_curve brett::convolve(
  discrete_curve const& data, discrete_curve const& kernel)
{
  if (data.empty())
    return data;

  // Apply a convolution with clampeing border handling
  assert(kernel.size() > 0 && kernel.size() & 1);
  int delta = kernel.size() / 2;
  auto N = static_cast<int>(data.size());
  auto M = static_cast<int>(kernel.size());
  auto highest = N - 1;
  discrete_curve result(data.size());
  for (int i = 0; i < N; ++i)
  {
    double sum = 0.0;

    for (int k = 0; k < M; ++k)
    {
      int sourceIndex = i + k - delta;
      if (sourceIndex < 0)
        sourceIndex = 0;
      else if (sourceIndex > highest)
        sourceIndex = highest;

      sum += data[sourceIndex] * kernel[k];
    }

    result[i] = sum;
  }
  return result;
}


double brett::interpolate(discrete_curve const& data, double x)
{
  if (data.empty())
    throw std::invalid_argument("Empty value list for interpolation");

  if (x < 0.0)
    return data.front();

  double begin = std::floor(x);
  auto i = static_cast<std::size_t>(begin);
  auto j = static_cast<std::size_t>(std::ceil(x));
  if (j >= data.size())
    return data.back();

  if (i == j)
    return data[i];

  double lambda = x - begin;
  return data[i] + lambda * (data[j] - data[i]);
}


double brett::find_relative(
  discrete_curve const& ascending_values, double which)
{
  if (ascending_values.empty())
  {
    throw std::invalid_argument("Given empty array to find value in");
  }
  if (which <= ascending_values.front())
    return 0.0;
  if (which >= ascending_values.back())
    return static_cast<double>(ascending_values.size() - 1);

  auto right =
    std::lower_bound(ascending_values.begin(), ascending_values.end(), which);
  auto left = right - 1;

  auto begin = *left;
  auto end = *right;

  auto relative = (which - begin) / (end - begin);

  return relative + (left - ascending_values.begin());
}


discrete_curve brett::gauss_kernel(std::size_t half_extends, double standard_deviation)
{
  if(standard_deviation <= 0.0)
  {
    throw std::runtime_error("Invalid standard deviation");
  }

  // Build a kernel for the gauss filter
  auto const N = 1 + half_extends * 2;
  discrete_curve kernel(N);

  const auto twoSigmaSquared = 2.0 * standard_deviation * standard_deviation;
  for (unsigned int i = 0; i <= half_extends; ++i)
  {
    auto delta = static_cast<double>(half_extends - i);
    double v = std::exp(-(delta * delta / twoSigmaSquared));
    kernel[i] = v;
    kernel[kernel.size() - 1 - i] = v;
  }

  // Normalize the kernel
  auto sum = std::accumulate(kernel.begin(), kernel.end(), 0.0);
  for (auto& each : kernel)
  {
    each /= sum;
  }

  return kernel;
}
