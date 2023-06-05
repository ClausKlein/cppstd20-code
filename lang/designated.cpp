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
#include <string>

#ifdef __cpp_lib_format
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

struct Value {
  double amount = 0;
  int precision = 2;
  std::string unit = "Dollar";
};

int main()
{
  Value v1{100};                               // OK
  Value v2{.amount = 100, .unit = "Euro"};     // OK
  Value v3{.precision = 8, .unit = "$"};       // OK

  //XXX Value v4{100, .unit = "Euro"};               // ERROR: all or none designated
  //XXX Value v5{.unit = "$", .amount = 20};         // ERROR: invalid order
  //XXX Value v6(.amount = 29.9, .unit = "Euro");    // ERROR: only supported for curly braces

  for (Value val : {v1, v2, v3}) {
    std::cout << format("{:.{}f} {}\n", val.amount, val.precision, val.unit);
  }
}

