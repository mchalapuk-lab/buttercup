// licence: GPLv3
// author: Maciej Chałapuk

#include "runner/run_suite.hpp"
#include "expect/expect_error.hpp"

#include <ftl/concepts/functor.h>
#include <ftl/list.h>

#include <chrono>

void buttercup::runner::run_suite(model::suite const& s,
                                  make_wait_notify wait_notify,
                                  model::async background,
                                  result_handlers const& result) {

  auto safe_run = [&wait_notify, &background, &result] (model::def def) {
    auto name = std::get<0>(def);
    model::provider<bool> wait;
    model::nullary notify;

    auto sec = std::chrono::seconds(std::get<2>(def));
    std::tie(wait, notify) = wait_notify(sec);

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

  auto run_sub_suites = [&] (model::suite const& suite) {
    run_suite(suite, wait_notify, background, result);
  };
  ftl::fmap(run_sub_suites, s.sub_suites);
}

