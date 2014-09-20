// licence: GPLv3
// author: Maciej Chałapuk

#ifndef BUTTERCUP_RUNNER_RUN_SUITE_HPP_
#define BUTTERCUP_RUNNER_RUN_SUITE_HPP_

#include "runner/wait_notify.hpp"
#include "runner/result_handlers.hpp"
#include "model/suite.hpp"
#include "expect/expect_error.hpp"

#include <ftl/concepts/functor.h>
#include <ftl/list.h>

#include <chrono>

namespace buttercup {
namespace runner {

void run_suite(model::suite const& s,
               make_wait_notify wait_notify,
               model::async background,
               result_handlers const& result);

} // namespace runner
} // namespace buttercup

#endif // include guard

