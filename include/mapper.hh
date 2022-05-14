#ifndef __MAPPER_HH__
#define __MAPPER_HH__

#include <functional>

template<class T, class U>
using Mapper = std::function<U(T const&)>;

// Less verbose than [](auto const&) { /* ... */ }
//   auto mapper = Map(x, x*2);
#define Map(x, body) [&](auto const& x) { return body; }

#endif // __MAPPER_HH__
