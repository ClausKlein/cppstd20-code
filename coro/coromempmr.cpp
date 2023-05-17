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
#include <string>
#include "corotaskpmr.hpp"
#include "tracknew.hpp"

CoroTaskPmr coro(int max)
{
  for (int val = 1; val <= max; ++val) {
    std::cout << "    coro(" << max << "): " << val << '\n';
    co_await std::suspend_always{};
  }
}

CoroTaskPmr coroStr(int max, std::string s)
{
  for (int val = 1; val <= max; ++val) {
    std::cout << "    coroStr(" << max << ", " << s << "): " << '\n';
    co_await std::suspend_always{};
  }
}

int main()
{
  TrackNew::trace();
  TrackNew::reset();

  coro(3);                             // initialize temporary coroutine
  coroStr(3, "hello");                 // initialize temporary coroutine

  auto coroTask = coro(3);             // initialize coroutine
  std::cout << "coro() started\n";
  while (coroTask.resume()) {          // RESUME
    std::cout << "coro() suspended\n";
  }
  std::cout << "coro() done\n";
}

