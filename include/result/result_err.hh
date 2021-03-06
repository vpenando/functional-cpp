#ifndef __RESULT_ERR_HH__
#define __RESULT_ERR_HH__

// Std
#include <ostream> // std::ostream

namespace result {

    // Err is used to build a Result with a given error value:
    //   auto result_err = Err(false); // Err<bool>
    //   Result<int, bool> result = result_err; // Ok!
    template<class T>
    class Err final {
    public:
        explicit Err(T const& value): _value(value) {
        }

        [[nodiscard]]
        inline bool is_ok() const noexcept {
            return false;
        }

        [[nodiscard]]
        inline bool is_err() const noexcept {
            return true;
        }

        [[nodiscard]]
        const T& value() const {
            return _value;
        }

        template<class _>
        [[nodiscard]]
        const Err map(_) const {
            return *this;
        }

        template<class U>
        [[nodiscard]]
        const Err<U> map_err(Mapper<T, U> const& mapper) const {
            return Err(mapper(value()));
        }

    private:
        T _value;
    };
    
} // namespace result

template<class T>
std::ostream& operator<<(std::ostream& stream, ::result::Err<T> const& err_value) {
    stream << "Err(" << err_value.value() << ")";
    return stream;
}

#endif // __RESULT_ERR_HH__
