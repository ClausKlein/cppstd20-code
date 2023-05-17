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


#include <iostream>
#include "coro.hpp"

int main()
{
  // start coroutine:
  auto coroTask = coro(3);             // initialize coroutine
  std::cout << "coro() started\n";

  // loop to resume the coroutine until it is done:
  while (coroTask.resume()) {          // RESUME
    std::cout << "coro() suspended\n";
  }

  std::cout << "coro() done\n";
}

