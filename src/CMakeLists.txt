set(HEADER_FILES
  ../include/brett/aligned_allocator.hpp
  ../include/brett/background_worker.hpp
  ../include/brett/cancellation_token.hpp
  ../include/brett/discrete_curve.hpp
  ../include/brett/overloaded.hpp
  ../include/brett/preempting_background_worker.hpp
  ../include/brett/select_overload.hpp
  ../include/brett/string_operations.hpp
  ../include/brett/version_info.hpp)

add_library(brett
  aligned_allocator.cpp
  background_worker.cpp
  discrete_curve.cpp
  preempting_background_worker.cpp
  string_operations.cpp)

target_include_directories(brett
  PUBLIC ../include)

target_link_libraries(brett
  PUBLIC pthread)

install(FILES ${HEADER_FILES}
  DESTINATION include/brett)

install(TARGETS brett
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
