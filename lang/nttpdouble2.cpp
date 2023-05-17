//********************************************************
// The following code example is taken from the book
//  C++20 - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppstd20.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#include <iostream>
#include <limits>
#include <type_traits>

template<double Val>
class MyClass {
};

int main()
{
  std::cout << std::boolalpha;
  std::cout << std::is_same_v<MyClass<42.0>, MyClass<17.7>>       // always false
            << '\n';
  std::cout << std::is_same_v<MyClass<42.0>, MyClass<126.0 / 3>>  // true or false
            << '\n';
  std::cout << std::is_same_v<MyClass<42.7>, MyClass<128.1/ 3>>   // true or false
            << "\n\n";

  std::cout << std::is_same_v<MyClass<0.1 + 0.3 + 0.00001>,
                              MyClass<0.3 + 0.1 + 0.00001>>       // true or false
            << '\n';

  std::cout << std::is_same_v<MyClass<0.1 + 0.3 + 0.00001>,
                              MyClass<0.00001 + 0.3 + 0.1>>       // true or false
            << "\n\n";

  constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
  std::cout << std::is_same_v<MyClass<NaN>, MyClass<NaN>>         // always true
            << '\n';
}

