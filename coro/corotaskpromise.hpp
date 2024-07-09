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

#include <coroutine>  // for suspend_always()
#include <exception>  // for terminate()

struct CoroTask::promise_type {
  auto get_return_object() {       // init and return the coroutine interface
    return CoroTask{CoroHdl::from_promise(*this)};
  }
  auto initial_suspend() {         // initial suspend point
    return std::suspend_always{};  // - suspend immediately
  }
  void unhandled_exception() {     // deal with exceptions
    std::terminate();              // - terminate the program
  }
  void return_void() {             // deal with the end or co_return;
  }
  auto final_suspend() noexcept {  // final suspend point
    return std::suspend_always{};  // - suspend immediately
  }
};

