#pragma once
#include <vector>

namespace brett
{

using discrete_curve = std::vector<double>;

discrete_curve convolve(discrete_curve const& data, discrete_curve const& kernel);
discrete_curve gauss(discrete_curve const& data, double sigma);

discrete_curve gauss_kernel(std::size_t half_extends, double standard_deviation);

double interpolate(discrete_curve const& data, double x);

/** Return a relative index into an ascending sequence.
    I.e. this is an inverse of the interpolation function for ascending values
*/
double find_relative(discrete_curve const& ascending_values, double which);

}
