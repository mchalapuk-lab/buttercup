// licence: GPLv3
// author: Maciej Chałapuk

#include <functional>

namespace buttercup {
namespace model {

typedef std::function<void()> nullary;

template <class arg_type>
using unary = std::function<void(arg_type)>;

template <class arg0_type, class arg1_type>
using binary = std::function<void(arg0_type, arg1_type)>;

template <class return_type>
using provider = std::function<return_type()>;

} // namespace model
} // namespace buttercup

