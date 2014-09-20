// licence: GPLv3
// author: Maciej Chałapuk

#ifndef BUTTERCUP_RUNNER_RESULT_HANDLERS_HPP_
#define BUTTERCUP_RUNNER_RESULT_HANDLERS_HPP_

#include "model/functions.hpp"

#include <string>

namespace buttercup {
namespace runner {

struct result_handlers {
  model::unary<std::string> success;
  model::binary<std::string, std::string> failure;
  model::binary<std::string, std::string> exception;
  model::unary<std::string> timeout;
  model::unary<std::string> unknown;
}; // struct result_handlers

} // namespace runner
} // namespace buttercup

#endif // include guard

