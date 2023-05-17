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

#pragma once

#include "always42.hpp"
#include <format>

//*** formatter for type Always42:
template<>
struct std::formatter<Always42>
{
  // use a standard int formatter that does the work:
#if __cpp_lib_format < 202106
  mutable    // in case the standard formatters have a non-const format()
#endif
  std::formatter<int> f;

  // delegate parsing to the standard int formatter:
#if __cpp_lib_format >= 202106
  constexpr  // in case standard formatters don't support constexpr parse() yet
#endif
  auto parse(std::format_parse_context& ctx) {
    return f.parse(ctx);
  }

  // delegate formatting of the int value to the standard int formatter:
  auto format(const Always42& obj, std::format_context& ctx) const {
    return f.format(obj.getValue(), ctx);
  }
};

