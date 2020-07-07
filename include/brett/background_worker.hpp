#pragma once
#include <thread>
#include <functional>
#include <deque>
#include <mutex>
#include <condition_variable>

namespace brett
{

class background_worker
{
public:
  using work = std::function<void()>;

  explicit background_worker();
  ~background_worker();

  void push(work executable);

private:
  void send_to_background(work executable);
  work pop();
  bool poll();
  void run();

  std::thread thread_;
  std::mutex mutex_;
  std::condition_variable condition_variable_;
  std::deque<work> queue_;
};

}
