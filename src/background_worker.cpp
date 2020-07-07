#include "../include/brett/background_worker.hpp"


using namespace brett;


background_worker::background_worker()
{
  thread_ = std::thread([this] {run();});
}


background_worker::~background_worker()
{
  send_to_background({});
  thread_.join();
}


bool background_worker::poll()
{
  auto next = pop();
  if (!next)
    return false;

  next();
  return true;
}


void background_worker::run()
{
  while (true)
  {
    try
    {
      if (!poll())
        return;
    }
    catch (...)
    {
      std::terminate();
    }
  }
}


background_worker::work background_worker::pop()
{
  std::unique_lock<std::mutex> lock(mutex_);
  condition_variable_.wait(lock, [this]{ return !queue_.empty();});
  auto result = queue_.front();
  queue_.pop_front();
  return result;
}


void background_worker::send_to_background(background_worker::work executable)
{
  std::unique_lock<std::mutex> lock(mutex_);
  queue_.push_back(std::move(executable));
  condition_variable_.notify_one();
}


void background_worker::push(background_worker::work executable)
{
  if (!executable)
    return;
  send_to_background(std::move(executable));
}
