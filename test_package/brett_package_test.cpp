#include <brett/string_operations.hpp>
#include <iostream>

int main()
{
  std::cout << brett::join({"schneide", "brett"}, " ") << std::endl;
  return 0;
}
