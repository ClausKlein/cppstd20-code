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


#include "tracingcoro.hpp"
#include "tracingawaiter.hpp"
#include <iostream>

TracingCoro coro(int max)
{
  std::cout << "  START coro(" << max << ")\n";
  for (int i = 1; i <= max; ++i) {
    std::cout << "  CORO: " << i << '/' << max << '\n';
    co_await TracingAwaiter{};          // SUSPEND
    std::cout << "  CONTINUE coro(" << max << ")\n";
  }
  std::cout << "  END coro(" << max << ")\n";
}

int main()
{
  // start coroutine:
  std::cout << "**** start coro()\n";
  auto coroTask = coro(3);              // init coroutine
  std::cout << "**** coro() started\n";

  // loop to resume the coroutine until it is done:
  std::cout << "\n**** resume coro() in loop\n";
  while (coroTask.resume()) {           // RESUME
    std::cout << "**** coro() suspended\n";
    //...
    std::cout << "\n**** resume coro() in loop\n";
  }

  std::cout << "\n**** coro() loop done\n";
}

