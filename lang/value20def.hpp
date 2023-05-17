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

#include <compare>

class Value {
 private:
  long id;
  //...
 public:
  constexpr Value(long i) noexcept
   : id{i} {
  }
  //...
  // for equality operators:
  bool operator== (const Value& rhs) const {
    return id == rhs.id;      // defines equality (== and !=)
  }
  // for relational operators:
  auto operator<=> (const Value& rhs) const {
    return id <=> rhs.id;     // defines ordering (<, <=, >, and >=)
  }
};

