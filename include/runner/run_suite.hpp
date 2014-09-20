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
               make_wait_notify make_wn_tuple,
               model::async background,
               result_handlers const& result) {

  auto safe_run = [&make_wn_tuple, &background, &result] (model::def def) {
    auto name = std::get<0>(def);
    model::provider<bool> wait;
    model::nullary notify;

    auto sec = std::chrono::seconds(std::get<2>(def));
    std::tie(wait, notify) = make_wn_tuple(sec);

    auto try_run = [&def, &notify, &result] () {
      auto name = std::get<0>(def);
      auto async_func = std::get<1>(def);

      try {
        async_func(notify);
        result.success(name);
      } catch (expect::expect_error const& fe) {
        result.failure(name, fe.what());
      } catch (std::exception const& ee) {
        result.exception(name, ee.what());
      } catch (...) {
        result.unknown(name);
      }
    };

    background(try_run);
    if (wait()) {
      result.timeout(name);
    }
  };

  auto run_test = [&s, &safe_run] (model::def const& def) {
    ftl::fmap(safe_run, s.before_each);
    safe_run(def);
    ftl::fmap(safe_run, s.after_each);
  };
  ftl::fmap(run_test, s.test_defs);

  using std::placeholders::_1;
  ftl::fmap(
      std::bind<void>(&run_suite, _1, make_wn_tuple, background, std::ref(result)),
      s.sub_suites
      );
}

} // namespace runner
} // namespace buttercup

#endif // include guard

