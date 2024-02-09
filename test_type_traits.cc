#include <iostream>
#include <type_traits>
#include "dbg.h"

int main() {
  using Type1 = uint64_t&;
  using Type2 = uint64_t&;
  using CommonType = std::common_type_t<Type1, Type2>;

  std::cout << "Type1: " << typeid(Type1).name() << std::endl;
  std::cout << "Type2: " << typeid(Type2).name() << std::endl;
  std::cout << "CommonType: " << typeid(CommonType).name() << std::endl;

  uint64_t a = 1;
  uint64_t b = 2;
  Type1 aa = a;
  Type2 bb = b;
  dbg(a);
  dbg(aa);
  dbg(b);
  dbg(bb);

  CommonType cc = a;
  dbg(cc);

  using Type3 =  decltype(aa);
  Type3 dd = a;
  dbg(dd);

  using Type4 = std::decay_t<Type3>;
  Type4 ee = a;
  dbg(ee);
  return 0;
}