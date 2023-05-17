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
#include "cororef.hpp"

int main()
{
  auto coroTask = coro(3);             // OOPS: creates reference to temporary/literal
  std::cout << "coro(3) started\n";
  coro(375);                           // another temporary coroutine
  std::cout << "coro(375) started\n";

  // loop to resume the coroutine until it is done:
  while (coroTask.resume()) {          // ERROR: undefined behavior
    std::cout << "coro() suspended\n";
  }

  std::cout << "coro() done\n";
}

