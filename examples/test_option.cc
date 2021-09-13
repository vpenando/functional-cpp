// Std
#include <cassert> // assert

// Others
#include <option.hh>

using option::Option;
using option::Some;
using option::None;

void test_option_some() {
    constexpr auto option_value = 42;
    const Option<int> option = Some(option_value);
    assert(option.is_some() && "option: must be Some(x)");
    assert(!option.is_none() && "option: must NOT be None");
    assert(option.value() == option_value && "option: invalid value");
    assert(option.value_or(0) == option_value && "option: invalid value_or");

    const auto map = [](const int val) {
        return val * 2;
    };
    constexpr auto expected_value = option_value * 2;
    const auto mapped = option.map<int>(map);
    assert(mapped.value() == expected_value && "mapped: invalid map");
    assert(mapped.is_some() && "mapped: must be Some(x)");
    assert(!mapped.is_none() && "mapped: must NOT be None");
    assert(mapped.value() == expected_value && "mapped: invalid value");
    assert(mapped.value_or(0) == expected_value && "mapped: invalid value_or");
}

void test_option_none() {
    const Option<int> option = None;
    (void)option;
    // TODO
}

void main() {
    test_option_some();
    test_option_none();
}
