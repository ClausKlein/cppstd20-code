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
#include "corotasksub.hpp"   // for CoroTaskSub

CoroTaskSub coro()
{
  std::cout << "    coro(): PART1\n";
  co_await std::suspend_always{};     // SUSPEND
  std::cout << "    coro(): PART2\n";
}

CoroTaskSub callCoro()
{
  std::cout << "  callCoro(): CALL coro()\n";
  co_await coro();                    // call sub-coroutine
  std::cout << "  callCoro(): coro() done\n";
  co_await std::suspend_always{};     // SUSPEND
  std::cout << "  callCoro(): END\n";
}

int main()
{
  auto coroTask = callCoro();           // initialize coroutine
  std::cout << "MAIN: callCoro() initialized\n";

  while (coroTask.resume()) {           // RESUME
    std::cout << "MAIN: callCoro() suspended\n";
  }

  std::cout << "MAIN: callCoro() done\n";
}

