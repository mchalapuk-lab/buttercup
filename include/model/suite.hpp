// licence: GPLv3
// author: Maciej Chałapuk

#include "model/def.hpp"
#include <list>

namespace buttercup {
namespace model {

struct suite {
  std::list<suite> sub_suites;
  std::list<def> before_each;
  std::list<def> after_each;
  std::list<def> test_defs;
}; // struct suite

} // namespace model
} // namespace buttercup

