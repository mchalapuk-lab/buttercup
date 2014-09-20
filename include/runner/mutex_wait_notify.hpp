// licence: GPLv3
// author: Maciej Chałapuk

#ifndef BUTTERCUP_RUNNER_MUTEX_WAIT_NOTIFY_HPP_
#define BUTTERCUP_RUNNER_MUTEX_WAIT_NOTIFY_HPP_

#include "runner/wait_notify.hpp"

#include <chrono>

namespace buttercup {
namespace runner {

wait_notify mutex_wait_notify(std::chrono::seconds);

} // namespace runner
} // namespace buttercup

#endif // include guard

