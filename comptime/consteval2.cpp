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


#include "consteval2.hpp"
#include <iostream>
#include <array>

int main()
{
  int i = 42;

  // using the square functions at runtime with runtime value:
  std::cout << squareR(i) << '\n';      // OK
  std::cout << squareCR(i) << '\n';     // OK
  std::cout << squareC(i) << '\n';      // ERROR

  // using the square functions at runtime with compile-time value:
  std::cout << squareR(42) << '\n';     // OK
  std::cout << squareCR(42) << '\n';    // OK
  std::cout << squareC(42) << '\n';     // OK: square computed at compile time

  // using the square functions at compile time:
  std::array<int, squareR(42)> arr1;    // ERROR
  std::array<int, squareCR(42)> arr2;   // OK: square computed at compile time
  std::array<int, squareC(42)> arr3;    // OK: square computed at compile time
  std::array<int, squareC(i)> arr4;     // ERROR
}


