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

#pragma once

#include <iostream>
#include <coroutine>      // for \Tstd::suspend_always{}
#include "corotask.hpp"   // for CoroTask

CoroTask coro(const int& max)
{
  std::cout << "  CORO " << max << " start\n";  // OOPS: value of max still valid?

  for (int val = 1; val <= max; ++val) {        // OOPS: value of max still valid?
    std::cout << "  CORO " << val << '/' << max << '\n';
    co_await std::suspend_always{};     // SUSPEND
  }

  std::cout << "  CORO " << max << " end\n";   // OOPS: value of max still valid?
}

