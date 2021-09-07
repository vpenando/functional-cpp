// Std
#include <iostream>

// Others
#include <option.hh>
#include <partial.hh>
#include <result.hh>

void example_result();
void example_option();
void example_partial();

int main() {
    example_result();
    std::cout << std::endl;

    example_option();
    std::cout << std::endl;

    example_partial();
    std::cout << std::endl;

    std::cout << "Press any key to continue...";
    std::cin.get();
}

void example_result() {
    using result::Result;
    using result::Ok;
    using result::Err;

    const Result<int, int> ok = Ok(42);
    const Result<int, int> err = Err(0);
    std::cout << ok << std::endl;
    std::cout << err << std::endl;
}

void example_option() {
    using option::Some;
    using option::None;

    const auto some = Some(42);
    const auto none = None;
    std::cout << some << std::endl;
    std::cout << none << std::endl;
}

void example_partial() {
    using partial::apply;

    const auto add = [](int x, int y) -> int {
        return x + y;
    };

    const auto add2 = apply(add, 2);
    const auto five = add2(3);
    std::cout << five << std::endl;
}
