// licence: GPLv3
// author: Maciej Chałapuk

#ifndef BUTTERCUP_BUILDER_SUITE_BUILDER_HPP_
#define BUTTERCUP_BUILDER_SUITE_BUILDER_HPP_

#include "model/functions.hpp"

#include <string>
#include <tuple>
#include <list>

#ifndef DEFAULT_TIMEOUT
#define DEFAULT_TIMEOUT 4
#endif

namespace buttercup {
namespace builder {

class suite_builder {
 public:
  void describe(std::string suite_name, model::sync suite_func) {
    describe(suite_name, wrap(suite_func));
  }
  void describe(std::string suite_name,
                model::async suite_func,
                int timeout_sec = DEFAULT_TIMEOUT) {
    sub_suites_.push_back(std::make_tuple(suite_name, suite_func, timeout_sec));
  }

  void beforeEach(std::string hook_name, model::sync hook_func) {
    beforeEach(hook_name, wrap(hook_func));
  }
  void beforeEach(std::string hook_name,
                  model::async hook_func,
                  int timeout_sec = DEFAULT_TIMEOUT) {
    before_each_.push_back(std::make_tuple(hook_name, hook_func, timeout_sec));
  }
  void afterEach(std::string hook_name, model::sync hook_func) {
    afterEach(hook_name, wrap(hook_func));
  }
  void afterEach(std::string hook_name,
                 model::async hook_func,
                 int timeout_sec = DEFAULT_TIMEOUT) {
    after_each_.push_back(std::make_tuple(hook_name, hook_func, timeout_sec));
  }

  void it(std::string test_name, model::sync test_func) {
    it(test_name, wrap(test_func));
  }
  void it(std::string suite_name,
          model::async test_func,
          int timeout_sec = DEFAULT_TIMEOUT) {
    test_defs_.push_back(std::make_tuple(suite_name, test_func, timeout_sec));
  }

  model::suite const build() const {
    return model::suite { sub_suites_, before_each_, after_each_, test_defs_ };
  }
 private:
  std::list<model::def> sub_suites_;
  std::list<model::def> before_each_;
  std::list<model::def> after_each_;
  std::list<model::def> test_defs_;

  static model::async wrap(model::sync func) {
    return [func] (model::nullary done) { func(); done(); };
  }
}; // struct suite_builder

} // namespace builder
} // namespace buttercup

#endif // include guard

