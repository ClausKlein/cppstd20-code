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


#include "coyield.hpp"
#include <iostream>

int main()
{
  // start coroutine:
  auto coroGen = coro(3);              // initialize coroutine
  std::cout << "coro() started\n";

  // loop to resume the coroutine until it is done:
  while (coroGen.resume()) {           // RESUME
    auto val = coroGen.getValue();
    std::cout << "coro() suspended with " << val << '\n';
  }

  std::cout << "coro() done\n";
}

