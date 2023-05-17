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
class ValOrColl {
  T value;
 public:
  ValOrColl(const T& val)
   : value{val} {
  }
  ValOrColl(T&& val)
   : value{std::move(val)} {
  }

  void print() const {
    std::cout << value << '\n';
  }

  void print() const requires std::ranges::range<T> {
    for (const auto& elem : value) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
};

