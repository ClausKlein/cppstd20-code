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

#include <coroutine>

// coroutine interface to deal with a simple task
// - providing resume() to resume the coroutine
class [[nodiscard]] CoroTask {
 public:
  // initialize members for state and customization:
  struct promise_type;    // definition later in corotaskpromise.hpp
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;            // native coroutine handle

 public:
  // constructor and destructor:
  CoroTask(auto h)
   : hdl{h} {             // store coroutine handle in interface
  }
  ~CoroTask() {
    if (hdl) {
      hdl.destroy();      // destroy coroutine handle
    }
  }
  // don't copy or move:
  CoroTask(const CoroTask&) = delete;
  CoroTask& operator=(const CoroTask&) = delete;

  // API to resume the coroutine
  // - returns whether there is still something to process
  bool resume() const {
    if (!hdl || hdl.done()) {
      return false;       // nothing (more) to process
    }
    hdl.resume();         // RESUME (blocks until suspended again or the end)
    return !hdl.done();
  }
};

#include "corotaskpromise.hpp"   // definition of promise_type

