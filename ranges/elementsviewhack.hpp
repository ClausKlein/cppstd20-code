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
#include <string>
#include <tuple>
// don't include <ranges> yet !!

struct Data {
  int id;
  std::string value;
};

std::ostream& operator<< (std::ostream& strm, const Data& d) {
    return strm << '[' << d.id << ": " << d.value << ']';
}

// tuple-like access to Data:
namespace std {
  template<>
  struct tuple_size<Data> : integral_constant<size_t, 2> {
  };

  template<>
  struct tuple_element<0, Data> {
    using type = int;
  };
  template<>
  struct tuple_element<1, Data> {
    using type = std::string;
  };

  template<size_t Idx> auto get(const Data& d) {
    if constexpr (Idx == 0) {
      return d.id;
    }
    else {
      return d.value;
    }
  }
} // namespace std

