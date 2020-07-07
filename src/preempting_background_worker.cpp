#include <brett/preempting_background_worker.hpp>

using namespace brett;


preempting_background_worker::preempting_background_worker()
{
  thread_ = std::thread([this]{run();});
}


preempting_background_worker::~preempting_background_worker()
{
  cancel_.cancel();
  condition_.notify_all();
  thread_.join();
}


void preempting_background_worker::run()
{
  while (true)
  {
    auto work = take_next();
    if (!work)
      break;

    (*work)(cancel_.token());
  }
}


std::optional<preempting_background_worker::Workload> preempting_background_worker::take_next()
{
  std::unique_lock<std::mutex> lock(mutex_);
  condition_.wait(lock, [this] {return cancel_.is_cancellation_requested() || scheduled_.has_value();});
  std::optional<Workload> result;
  result.swap(scheduled_);
  return result;
}


void preempting_background_worker::push(Workload const& e)
{
  std::unique_lock<std::mutex> lock(mutex_);
  scheduled_ = e;
  condition_.notify_all();
  cancel_.cancel_and_reset();
}

