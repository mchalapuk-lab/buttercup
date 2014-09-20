// licence: GPLv3
// author: Maciej Chałapuk

#include "runner/mutex_wait_notify.hpp"

#include <memory>
#include <mutex>
#include <condition_variable>

namespace buttercup {
namespace runner {

wait_notify mutex_wait_notify(std::chrono::seconds seconds) {
  auto mutex = std::make_shared<std::mutex>();
  auto cv = std::make_shared<std::condition_variable>();

  auto wait = [mutex, cv, seconds] () {
    std::unique_lock<std::mutex> lock(*mutex);
    auto result = cv->wait_for(lock, seconds);
    return (std::cv_status::timeout == result);
  };
  auto notify = [mutex, cv] () {
    std::unique_lock<std::mutex> lock(*mutex);
    cv->notify_one();
  };
  return std::make_tuple(wait, notify);
}

} // namespace runner
} // namespace buttercup

