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


#include "coyieldback.hpp"
#include <iostream>
#include <vector>

int main()
{
  // start coroutine:
  auto coroGen = coro(3);              // initialize coroutine
  std::cout << "**** coro() started\n";

  // loop to resume the coroutine until it is done:
  std::cout << "\n**** resume coro()\n";
  while (coroGen.resume()) {           // RESUME
    // process value from co_yield:
    auto val = coroGen.getValue();
    std::cout << "**** coro() suspended with " << val << '\n';

    // set response (the value co_yield yields):
    std::string back = (val % 2 != 0 ? "OK" : "ERR");  
    std::cout << "\n**** resume coro() with back value: " << back << '\n';
    coroGen.setBackValue(back);        // set value back to the coroutine
  }

  std::cout << "**** coro() done\n";
}

