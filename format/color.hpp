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

#include <format>
#include <string>

enum class Color { red, green, blue };

//*** formatter for enum type Color:
template<>
struct std::formatter<Color> : public std::formatter<std::string>
{
  auto format(Color c, format_context& ctx) const {
    // initialize a string for the value:
    std::string value;
    switch (c) {
      using enum Color;
      case red:
        value = "red";
        break;
      case green:
        value = "green";
        break;
      case blue:
        value = "blue";
        break;
      default:
        value = std::format("Color{}", static_cast<int>(c));
        break;
    }
    // and delegate the rest of formatting to the string formatter:
    return std::formatter<std::string>::format(value, ctx);
  }
};

