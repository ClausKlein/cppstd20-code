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

#include <iostream>
#include <ranges>

template<typename T>
void printColl(T&& obj, int level = 0)
{
  if constexpr(std::same_as<std::remove_cvref_t<T>, std::string>) {
    std::cout << "\"" << obj << "\"";
  }
  else if constexpr(std::ranges::input_range<T>) {
    std::cout << '[';
    for (auto pos = obj.begin(); pos != obj.end(); ++pos) {
       printColl(*pos, level+1);
       if (std::ranges::next(pos) != obj.end()) {
         std::cout << ' ';
       }
    }
    std::cout << ']';
  }
  else {
    std::cout << obj;
  }
  if (level == 0) { std::cout << '\n'; }
}

