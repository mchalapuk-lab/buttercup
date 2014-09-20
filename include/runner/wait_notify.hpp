// licence: GPLv3
// author: Maciej Chałapuk

#include "model/functions.hpp"

#include <functional>
#include <tuple>
#include <chrono>

namespace buttercup {
namespace runner {

typedef std::tuple<model::provider<bool>, model::nullary> wait_notify;
typedef std::function<wait_notify(std::chrono::seconds)> make_wait_notify;

} // namespace runner
} // namespace buttercup

