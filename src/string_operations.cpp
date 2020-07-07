#include <brett/string_operations.hpp>
#include <algorithm>
#include <cctype>


namespace
{

std::pair<std::string::size_type, std::size_t> findNextOf(
  std::string const& text, std::size_t offset,
  std::vector<std::string> const& search)
{
  auto begin = std::string::npos;
  auto end = std::string::npos;

  for (auto const& each : search)
  {
    auto found = text.find(each, offset);
    if (found < begin)
    {
      begin = found;
      end = found + each.size();
    }
  }

  return std::make_pair(begin, end);
}

}  // namespace


std::string brett::join(
  std::vector<std::string> const& options, std::string const& separator)
{
  if (options.empty())
    return {};

  auto i = options.begin();
  std::string result = *i;
  ++i;
  for (; i != options.end(); ++i)
  {
    result += separator;
    result += *i;
  }

  return result;
}


std::vector<std::string> brett::split(std::string const& message, char delimiter)
{
  if (message.empty())
    return {};

  std::vector<std::string> result;
  auto last = std::string::size_type(0);
  auto x = message.find(delimiter);

  while (true)
  {
    result.push_back(message.substr(last, x - last));
    if (x == std::string::npos)
      break;

    last = x + 1;
    x = message.find(delimiter, x + 1);
  }

  return result;
}


std::vector<std::string> brett::split(
  std::string const& message, std::vector<std::string> const& delimiter)
{
  if (message.empty())
    return {};

  std::vector<std::string> result;
  auto last = std::string::size_type(0);
  auto x = findNextOf(message, 0, delimiter);

  while (true)
  {
    if (x.first == std::string::npos)
    {
      result.push_back(message.substr(last));
      break;
    }
    else
    {
      result.push_back(message.substr(last, x.first - last));
    }

    last = x.second;
    x = findNextOf(message, last, delimiter);
  }

  return result;
}


std::string brett::to_lower(std::string rhs)
{
  // Convert to lower case to make section/name lookups case-insensitive
  std::transform(rhs.begin(), rhs.end(), rhs.begin(),
    [](char x) { return std::tolower(x); });
  return rhs;
}

std::vector<std::string> brett::split(std::string const& text, std::string const& delimiter)
{
  std::vector <std::string> result;

  std::size_t position = 0;
  do
  {
    auto split = text.find(delimiter, position);

    if (split == std::string::npos)
      break;

    result.push_back(text.substr(position, split - position));
    position = split + 1;

  } while (true);

  result.push_back(text.substr(position));
  return result;
}
