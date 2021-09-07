#ifndef __OPTION_HH__
#define __OPTION_HH__

// Std
#include <cassert>     // assert
#include <memory>      // std::shared_ptr, std::make_shared
#include <ostream>     // std::ostream
#include <type_traits> // std::remove_reference_t

// Others
#include <mapper.hh>

namespace option {

    // This is the class that represents an optional value.
    template<class TValue>
    class Option;


    // Some is used to construct an Option with a given value:
    //   auto opt = Some(42); // Option<int>
    // 
    // Assigning Some(x) to an Option will result in:
    //   opt.is_some() == true;
    //   opt.is_none() == false;
    template<class TValue>
    Option<TValue> Some(TValue const& value);


    namespace details {

        // None_t is the type that is used to assign None to an Option:
        //   Option<T> my_option = None;
        class None_t final {
        public:
            inline bool is_some() const noexcept {
                return false;
            }

            inline bool is_none() const noexcept {
                return true;
            }

            template<class T>
            T value_or(T const& default_value) const {
                return default_value;
            }

            template<class Mapper>
            const None_t map(Mapper const&) const {
                // Todo: static_assert that Mapper is callable
                return *this;
            }

            // Note: None_t doesn't have a member function 'value' in order
            // to fail at compile-time if we attempt to call it.
        };
    }


    // None is used to construct an empty Option:
    //   Option<T> opt = None;
    // 
    // Assigning None to an Option will result in:
    //   opt.is_some() == false;
    //   opt.is_none() == true;
    static constexpr ::option::details::None_t None{};


    template<class TValue>
    class Option final {
        using Value = std::remove_reference_t<TValue>;
        using OptionalValue = std::shared_ptr<Value>;

        // Needed to access private ctor.
        template<class T>
        friend Option<T> Some(T const& value);

    public:
        Option(::option::details::None_t) noexcept {}

        inline bool is_some() const noexcept {
            return _optional_value != nullptr;
        }

        inline bool is_none() const noexcept {
            return !is_some();
        }

        template<class U>
        const Option<U> map(Mapper<TValue, U> const& mapper) const {
            if (is_none()) {
                return None;
            }
            assert(is_some());
            auto value = mapper(*_optional_value);
            return Some(value);
        }

        const Value& value() const noexcept { // Note: OptionalValue::op* is noexcept
            assert(_optional_value != nullptr);
            return *_optional_value;
        }

        const Value& value_or(Value const& default_value) const {
            if (is_none()) {
                return default_value;
            }
            assert(is_some());
            return value();
        }

    private:
        OptionalValue _optional_value;

        Option(Value const& value) {
            _optional_value = std::make_shared<Value>(value);
        }
    };

    template<class T>
    Option<T> Some(T const& value) {
        return Option<T>(value);
    }
}


template<class T>
std::ostream& operator<<(std::ostream& stream, ::option::Option<T> const& option) {
    return (option.is_some())
        ? stream << "Some(" << option.value() << ")"
        : stream << "None";
}

std::ostream& operator<<(std::ostream& stream, ::option::details::None_t) {
    return stream << "None";
}

#endif // __OPTION_HH__