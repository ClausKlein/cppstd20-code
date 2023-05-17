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

#include "coropriosched2.hpp"
#include <iostream>

CoroPrioTask coro(int max)
{
  std::cout << "    coro(" << max << ")\n";
  for (int val = 1; val <= max; ++val) {
    std::cout << "    coro(" << max << "): " << val << '\n';
    co_await CoroPrioRequest::less;   // SUSPEND with lower prio
  }
  std::cout << "    end coro(" << max << ")\n";
}

