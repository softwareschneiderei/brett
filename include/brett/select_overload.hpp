#pragma once

namespace brett
{

template <typename... Args>
struct select_overload
{
  template <typename C, typename R>
  static constexpr auto of(R (C::*pmf)(Args...)) -> decltype(pmf)
  {
    return pmf;
  }
};

}
