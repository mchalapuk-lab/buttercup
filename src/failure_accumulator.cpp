// licence: GPLv3
// author: Maciej Chałapuk

#include "runner/failure_accumulator.hpp"

namespace buttercup {
namespace runner {

result_handlers failure_accumulator(std::list<failure> &failures) {
  auto addUnary = [&failures] (fail_type type) {
    return [&failures, type] (std::string name) {
      failures.push_back(std::make_tuple(name, type));
    };
  };
  auto addBinary = [&failures] (fail_type type) {
    return [&failures, type] (std::string name, std::string message) {
      failures.push_back(std::make_tuple(name + ": " + message, type));
    };
  };

  using namespace std::placeholders;
  return result_handlers {
    [] (std::string) {},
    addBinary(fail_type::ASSERTION),
    addBinary(fail_type::EXCEPTION),
    addUnary(fail_type::TIMEOUT),
    addUnary(fail_type::UNKNOWN),
  };
}

} // namespace runner
} // namespace buttercup

