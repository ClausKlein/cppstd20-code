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

#include "backawaiter.hpp"
#include <coroutine>
#include <exception>   // for terminate()
#include <string>

class [[nodiscard]] CoroGenBack {
 public:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;                         // native coroutine handle

 public:
  struct promise_type {
    int coroValue = 0;                 // value TO caller on suspension
    std::string backValue;             // value back FROM caller after suspension

    auto yield_value(int val) {        // reaction to co_yield
      coroValue = val;                 // - store value locally
      backValue.clear();               // - reinit back value
      return BackAwaiter<CoroHdl>{};   // - use special awaiter for response
    }

    // the usual members:
    auto get_return_object() { return CoroHdl::from_promise(*this); }
    auto initial_suspend() { return std::suspend_always{}; }
    void return_void() { }
    void unhandled_exception() { std::terminate(); }
    auto final_suspend() noexcept { return std::suspend_always{}; }
  };

  // constructors and destructor:
  CoroGenBack(auto h) : hdl{h} { }
  ~CoroGenBack() { if (hdl) hdl.destroy(); }

  // no copying or moving:
  CoroGenBack(const CoroGenBack&) = delete;
  CoroGenBack& operator=(const CoroGenBack&) = delete;

  // API:
  // - resume the coroutine:
  bool resume() const {
    if (!hdl || hdl.done()) {
      return false;    // nothing (more) to process
    }
    hdl.resume();      // RESUME
    return !hdl.done();
  }

  // - yield value from co_yield:
  int getValue() const {
    return hdl.promise().coroValue;
  }

  // - set value back to the coroutine after suspension:
  void setBackValue(const auto& val) {
    hdl.promise().backValue = val;
  }
};

