// licence: GPLv3
// author: Maciej Chałapuk

#ifndef BUTTERCUP_RUNNER_FAILURE_ACCUMULATOR_HPP_
#define BUTTERCUP_RUNNER_FAILURE_ACCUMULATOR_HPP_

#include "runner/result_handlers.hpp"

#include <string>
#include <tuple>
#include <list>

namespace buttercup {
namespace runner {

enum class fail_type {
  ASSERTION,
  EXCEPTION,
  TIMEOUT,
  UNKNOWN,
};

typedef std::tuple<std::string, fail_type> failure;

result_handlers failure_accumulator(std::list<failure> &);

} // namespace runner
} // namespace buttercup

#endif // include guard

