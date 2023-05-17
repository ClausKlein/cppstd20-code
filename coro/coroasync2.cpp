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


#include "coroasync.hpp"
#include <iostream>

int main()
{
  // init pool of coroutine threads:
  syncOut() << "**** main() on thread " << std::this_thread::get_id()
            << std::endl;
  CoroPool pool{4};

  // start multiple coroutines and run them in coroutine pool:
  for (int i = 1; i <= 4; ++i) {
    syncOut() << "runTask(runAsync(" << i << "))" << std::endl;
    pool.runTask(runAsync(std::to_string(i)));
  }

  // wait until all coroutines are done:
  syncOut() << "\n**** waitUntilNoCoros()" << std::endl;
  pool.waitUntilNoCoros();

  syncOut() << "\n**** main() done" << std::endl;
}

