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


#include "isconsteval.hpp"
#include <iostream>

int main()
{
  constexpr int l1 = len("hello");  // uses then branch
  int l2 = len("hello");            // uses else branch (no required compile-time context) 
  std::cout << "l1: " << l1 << '\n';
  std::cout << "l2: " << l2 << '\n';
}

