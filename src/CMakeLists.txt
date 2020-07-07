add_library(brett
  ../include/brett/background_worker.hpp
  background_worker.cpp
  ../include/brett/cancellation_token.hpp
  ../include/brett/discrete_curve.hpp
  discrete_curve.cpp
  ../include/brett/preempting_background_worker.hpp
  preempting_background_worker.cpp
  ../include/brett/select_overload.hpp
  ../include/brett/string_operations.hpp
  string_operations.cpp
  ../include/brett/version_info.hpp)

target_include_directories(brett
  PUBLIC ../include)

target_link_libraries(brett
  PUBLIC pthread)
