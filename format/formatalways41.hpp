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

#include "always41.hpp"
#include <format>

template<>
class std::formatter<Always41>
{
  int width = 0;  // specified width of the field
 public:
  // parse the format string for this type:
  constexpr auto parse(std::format_parse_context& ctx) {
    auto pos = ctx.begin();
    while (pos != ctx.end() && *pos != '}') {
      if (*pos < '0' || *pos > '9') {
        throw std::format_error{std::format("invalid format '{}'", *pos)};
      }
      width = width * 10 + *pos - '0';  // new digit for the width
      ++pos;
    }
    return pos;            // return position of }
  }

  // format by always writing its value:
  auto format(const Always41& obj, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "{:{}}", obj.getValue(), width);
  }
};

