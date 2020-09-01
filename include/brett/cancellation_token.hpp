#pragma once
#include <atomic>
#include <memory>

namespace brett
{

class cancellation_token
{
public:
  cancellation_token() = default;
  cancellation_token(cancellation_token const&) = default;
  cancellation_token(cancellation_token&&) = default;

  cancellation_token& operator=(cancellation_token const&) = default;
  cancellation_token& operator=(cancellation_token&&) = default;

  [[nodiscard]] bool is_cancellation_requested() const
  {
    return state_ && *state_;
  }

private:
  explicit cancellation_token(std::shared_ptr<std::atomic_bool const> state)
  : state_(std::move(state))
  {
  }

  std::shared_ptr<std::atomic_bool const> state_;

  friend class cancellation_source;
};

class cancellation_source
{
public:
  cancellation_source()
  : state_(std::make_shared<std::atomic_bool>(false))
  {
  }

  void cancel()
  {
    *state_ = true;
  }

  /** Mark all connected tokens as cancelled and sever the connection to them.
   */
  void cancel_and_reset()
  {
    auto other = std::make_shared<std::atomic_bool>(false);
    state_.swap(other);
    *other = true;
  }

  [[nodiscard]] bool is_cancellation_requested() const
  {
    return state_ && *state_;
  }

  [[nodiscard]] cancellation_token token() const
  {
    return cancellation_token(state_);
  }

private:
  std::shared_ptr<std::atomic_bool> state_;
};

}
