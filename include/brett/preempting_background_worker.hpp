#pragma once

#include <thread>
#include <condition_variable>
#include <atomic>
#include <optional>
#include <functional>
#include "cancellation_token.hpp"

namespace brett
{

class preempting_background_worker
{
public:
  using Workload = std::function<void(cancellation_token)>;

  explicit preempting_background_worker();
  /**
   * Destruct the worker and end the worker thread. Outstanding work is finished before.
   */
  ~preempting_background_worker();

  /**
   * Add new work do be executed asap. This will overwrite scheduled, but not already executing, work.
   * @param e
   */
  void push(Workload const& e);
private:
  void run();

  std::optional<Workload> take_next();

  std::thread thread_;
  std::optional<Workload> scheduled_;
  std::condition_variable condition_;
  std::mutex mutex_;
  cancellation_source cancel_;
};

}
