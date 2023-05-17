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
#include "corogenback.hpp"   // for CoroGenBack

CoroGenBack coro(int max)
{
  std::cout << "         CORO " << max << " start\n";

  for (int val = 1; val <= max; ++val) {
    // print next value:
    std::cout << "         CORO " << val << '/' << max << '\n';

    // yield next value:
    auto back = co_yield val;           // SUSPEND with value with response
    std::cout << "         CORO => " << back << "\n";
  }

  std::cout << "         CORO " << max << " end\n";
}

