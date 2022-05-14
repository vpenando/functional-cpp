#ifndef __RESULT_OK_HH__
#define __RESULT_OK_HH__

// Std
#include <ostream> // std::ostream

namespace result {

    // Ok is used to build a Result with a given OK value:
    //   auto result_ok = Ok(42); // Ok<int>
    //   Result<int, bool> result = result_ok; // Ok!
    template<class T>
    class Ok final {
    public:
        explicit Ok(T const& value): _value(value) {
        }

        [[nodiscard]]
        inline bool is_ok() const noexcept {
            return true;
        }

        [[nodiscard]]
        inline bool is_err() const noexcept {
            return false;
        }

        [[nodiscard]]
        const T& value() const {
            return _value;
        }

        template<class U>
        [[nodiscard]]
        const Ok<U> map(Mapper<T, U> const& mapper) const {
            return Ok(mapper(value()));
        }

        template<class _>
        [[nodiscard]]
        const Ok map_err(_) const {
            return *this;
        }

    private:
        T _value;
    };

} // namespace result

template<class T>
std::ostream& operator<<(std::ostream& stream, ::result::Ok<T> const& ok_value) {
    stream << "Ok(" << ok_value.value() << ")";
    return stream;
}

#endif // __RESULT_OK_HH__
