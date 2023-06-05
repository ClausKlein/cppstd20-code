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

#include <string>

#ifdef __cpp_lib_format
#include <format>
using std::format;
#else
#include <fmt/format.h>
using fmt::format;
#endif

// convert an integral value to a std::string
// - can be called at compile time or runtime
constexpr std::string asString(long long value)
{
  if (std::is_constant_evaluated()) {
    // compile-time version:
    if (value == 0) {
      return "0";
    }

    if (value < 0) {
      return "-" + asString(-value);
    }

    std::string s = asString(value / 10) + std::string(1, static_cast<char>(value % 10 + '0'));
    if (s.size() > 1 && s[0] == '0') {  // skip leading 0 if there is one
      s.erase(0, 1);
    }
    return s;
  }
  else {
    // runtime version:
    return format("{}", value);
  }
}

