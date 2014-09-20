// licence: GPLv3
// author: Maciej Chałapuk

#include "model/sync.hpp"
#include "runner/failure_accumulator.hpp"
#include "runner/run_suite.hpp"

#include "test/stub_wait_notify.hpp"

#include "gtest/gtest.h"

using namespace buttercup;

TEST(runner_run_suite, simple_test) {
  std::list<runner::failure> failures;
  
  model::suite suite {
    std::list<model::suite>(),
    std::list<model::def>(),
    std::list<model::def>(),
    std::list<model::def>(),
  };

  auto fake_background = [] (model::sync f) { f(); };

  runner::run_suite(
      suite,
      &test::stub_wait_notify,
      fake_background,
      runner::failure_accumulator(failures)
      );

  ftl::fmap(
      [] (runner::failure f) { std::cerr << std::get<0>(f) << std::endl; },
      failures
      );
}

