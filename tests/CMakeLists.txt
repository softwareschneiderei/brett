add_executable(brett_tests
  aligned_allocator.t.cpp
  discrete_curve.t.cpp
  preempting_background_worker.t.cpp
  string_operations.t.cpp
  test_runner.cpp)

target_link_libraries(brett_tests
  PUBLIC brett
  PUBLIC Catch2::Catch2)
