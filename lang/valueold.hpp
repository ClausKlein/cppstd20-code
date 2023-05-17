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

class Value {
 private:
  long id;
  //...
 public:
  constexpr Value(long i) noexcept  // supports implicit type conversion
   : id{i} {
  }
  //...
  // equality operators:
  [[nodiscard]] friend constexpr
  bool operator== (const Value& lhs, const Value& rhs) noexcept {
    return lhs.id == rhs.id;      // basic check for equality
  }
  [[nodiscard]] friend constexpr
  bool operator!= (const Value& lhs, const Value& rhs) noexcept {
    return !(lhs == rhs);         // derived check for inequality
  }

  // relational operators:
  [[nodiscard]] friend constexpr
  bool operator< (const Value& lhs, const Value& rhs) noexcept {
    return lhs.id < rhs.id;       // basic check for ordering
  }
  [[nodiscard]] friend constexpr
  bool operator<= (const Value& lhs, const Value& rhs) noexcept {
    return !(rhs < lhs);          // derived check
  }
  [[nodiscard]] friend constexpr
  bool operator> (const Value& lhs, const Value& rhs) noexcept {
    return rhs < lhs;             // derived check
  }
  [[nodiscard]] friend constexpr
  bool operator>= (const Value& lhs, const Value& rhs) noexcept {
    return !(lhs < rhs);          // derived check
  }
};

