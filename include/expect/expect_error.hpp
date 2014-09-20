// licence: GPLv3
// author: Maciej Chałapuk

#include "model/functions.hpp"

namespace buttercup {
namespace expect {

struct expect_error : std::runtime_error {
  expect_error(std::string message) : std::runtime_error(message) {}
}; // struct expect_error

} // namespace expect
} // namespace buttercup

