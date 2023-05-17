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

#include <type_traits>  // for std::is_convertible_v<>

template<typename T>
class Wrapper {
    T value;
  public:
    template<typename U>
    explicit(!std::is_convertible_v<U, T>)
    Wrapper(const U& val)
     :value{val} {
    }
    //...
};

