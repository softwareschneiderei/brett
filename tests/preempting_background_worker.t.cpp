#include <catch2/catch.hpp>
#include <brett/preempting_background_worker.hpp>

TEST_CASE("Workers lifetime is finite")
{
  {
    brett::preempting_background_worker worker;
  }
  REQUIRE(true);
}

TEST_CASE("Executes simple work")
{
  std::atomic_bool was_executed{false};

  {
    brett::preempting_background_worker worker;
    worker.push([&] (brett::cancellation_token const&) { was_executed=true;});
  }

  REQUIRE(was_executed);
}
