add_executable(brett_tests
  discrete_curve.t.cpp
  preempting_background_worker.t.cpp
  test_runner.cpp)

target_link_libraries(brett_tests
  PUBLIC brett
  PUBLIC CONAN_PKG::Catch2)
