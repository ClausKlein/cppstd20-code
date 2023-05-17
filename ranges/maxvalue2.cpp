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


#include "maxvalue2.hpp"
#include <iostream>
#include <algorithm>

int main()
{
  int arr[] = {0, 8, 15, 42, 7};

  // max value of a filtered range:
  auto odd = [] (auto val) {                      // predicate for odd values
               return val % 2 != 0;
             };
  std::cout << maxValue(arr | std::views::filter(odd)) << '\n';  // OK
}

