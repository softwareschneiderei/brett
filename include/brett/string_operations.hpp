#pragma once
#include <string>
#include <vector>

namespace brett
{

std::string join(std::vector<std::string> const& options, std::string const& separator);

std::vector<std::string> split(std::string const& message, char delimiter);
std::vector<std::string> split(std::string const& message, std::vector<std::string> const& delimiter);
std::vector<std::string> split(std::string const& text, std::string const& delimiter);

std::string to_lower(std::string rhs);

}
