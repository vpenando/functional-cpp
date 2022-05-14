#ifndef __RESULT_HH__
#define __RESULT_HH__

// Std
#include <ostream> // std::ostream

// Others
#include <mapper.hh>
#include <option.hh>
#include <result/result_err.hh>
#include <result/result_ok.hh>

namespace result {

    // Result is the same Result as we can find in Rust, OCaml, ...
    // It provides two variants, Ok and Err, which represent respectively a 'good case' and a 'bad case'.
    //   Result<int, bool> r1 = Ok(42);
    //   Result<int, bool> r2 = Err(false);
    template<class TOk, class TErr>
    class Result final {

        // Ex:
        //   Result<T, U> result = Ok(x);
        //   std::cout << result;  // "Ok(...)"
        friend std::ostream& operator<<(std::ostream& stream, Result<TOk, TErr> const& result) {
            return (result.is_ok())
                ? stream << "Ok(" << result._result_ok.value() << ")"
                : stream << "Err(" << result._result_err.value() << ")";
        }

    public:
        Result(Ok<TOk> const& result_ok):
            _result_ok(::option::Some(result_ok.value())),
            _result_err(::option::None)
        {
        }

        Result(Err<TErr> const& result_err):
            _result_ok(::option::None),
            _result_err(::option::Some(result_err.value()))
        {
        }

        [[nodiscard]]
        inline bool is_ok() const noexcept {
            return _result_ok.is_some();
        }

        [[nodiscard]]
        inline bool is_err() const noexcept {
            return _result_err.is_some();
        }

        template<class U>
        [[nodiscard]]
        const Result<U, TErr> map(Mapper<TOk, U> const& mapper) const {
            if (is_ok()) {
                return Ok(_result_ok.map(mapper).value());
            }
            return Err(_result_err.value());
        }

        template<class U>
        [[nodiscard]]
        const Result<TOk, U> map_err(Mapper<TErr, U> const& mapper) const {
            if (is_err()) {
                return Err(_result_err.map(mapper).value());
            }
            return Ok(_result_ok.value());
        }

        [[nodiscard]]
        const TOk& value_or(TOk const& default_value) const {
            return _result_ok.value_or(default_value);
        }

        [[nodiscard]]
        const TErr& error_or(TErr const& default_value) const {
            return _result_err.value_or(default_value);
        }

    private:

        // Note: If Ok, _result_err is always None.
        //       If Err, _result_ok is always None.
        // Todo: Provide two different implementations of Result to avoid
        //       handling an empty Option?
        const ::option::Option<TOk> _result_ok;
        const ::option::Option<TErr> _result_err;
    };

}

#endif // __RESULT_HH__
