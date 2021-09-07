#ifndef __PARTIAL_HH__
#define __PARTIAL_HH__
  
/* Example:
 
    auto add(int a, int b) {
      return a + b;
    }
  
    const auto add2 = partial::apply(add, 2);
    const auto five = add2(3);
 
*/
  
namespace partial {

    template<class Fn, class T>
    auto apply(Fn const& fn, T const& val){
        return [&](auto const& ...other_args){
            return fn(val, other_args...);
        };
    }

    template<class Fn, class ...Args>
    auto apply(Fn const& fn, Args const& ...args){
        return [&](auto const& ...other_args){
            return fn(args..., other_args...);
        };
    }  
}

#endif // __PARTIAL_HH__
