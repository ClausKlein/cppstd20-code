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


#include "color.hpp"
#include <iostream>
#include <string>
#include <format>

int main()
{
  for (auto val : {Color::red, Color::green, Color::blue, Color{13}}) {
    // use user-provided formatter for enum Color:
    std::cout << std::format("Color {:_>8} has value {:02}\n",
                             val, static_cast<int>(val));
  }
}

