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
  // start two coroutines:
  auto coroTask1 = coro(3);            // initialize 1st coroutine
  auto coroTask2 = coro(5);            // initialize 2nd coroutine
  std::cout << "coro(3) and coro(5) started\n";

  coroTask2.resume();                  // RESUME 2nd coroutine once

  // loop to resume the 1st coroutine until it is done:
  while (coroTask1.resume()) {         // RESUME 1st coroutine
    std::cout << "coro() suspended\n";
  }

  std::cout << "coro() done\n";

  coroTask2.resume();                  // RESUME 2nd coroutine again
}

