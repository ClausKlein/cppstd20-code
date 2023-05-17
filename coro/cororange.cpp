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


#include "cororange.hpp"
#include <iostream>
#include <vector>

int main()
{
  auto gen = coro(3);              // initialize coroutine
  std::cout << "--- coro() started\n";

  // loop to resume the coroutine for the next value:
  for (const auto& val : gen) {
    std::cout << "    val: " << val << '\n';
  }

  std::cout << "--- coro() done\n";
}

