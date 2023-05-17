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


#include "coroprio2.hpp"
#include <iostream>

int main()
{
  std::cout << "start main()\n";
  CoroPrioScheduler sched;

  std::cout << "schedule coroutines\n";
  sched.start(coro(5));
  sched.start(coro(1));
  sched.start(coro(4));

  std::cout << "loop until all are processed\n";
  while (sched.resumeNext()) {
  }

  std::cout << "end main()\n";
}

