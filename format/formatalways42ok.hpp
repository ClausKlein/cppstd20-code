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
  std::formatter<int> f;

  // delegate parsing to the standard formatter:
  constexpr auto parse(std::format_parse_context& ctx) {
    return f.parse(ctx);
  }

  // delegate formatting of the value to the standard formatter:
  auto format(const Always42& obj, std::format_context& ctx) const {
    return f.format(obj.getValue(), ctx);
  }
};

