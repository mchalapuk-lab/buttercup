// licence: GPLv3
// author: Maciej Chałapuk

#ifndef BUTTERCUP_TEST_STUB_WAIT_NOTIFY_HPP_
#define BUTTERCUP_TEST_STUB_WAIT_NOTIFY_HPP_

#include "model/functions.hpp"
#include "runner/wait_notify.hpp"

namespace buttercup {
namespace test {

runner::wait_notify stub_wait_notify(std::chrono::seconds seconds) {
  return std::make_tuple(
      model::provider<bool>([] () { return false; }),
      model::nullary([] () {})
      );
}

} // namespace test
} // namespace buttercup

#endif // include guard

