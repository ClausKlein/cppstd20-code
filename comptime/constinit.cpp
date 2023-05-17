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


#include "truthc.hpp"
#include <iostream>

constinit int val = theTruth.value ;  // initialized after theTruth is initialized

int main()
{
  std::cout << val << '\n';   // guaranteed to be 42
  ++val;
  std::cout << val << '\n';   // guaranteed to be 43
}

