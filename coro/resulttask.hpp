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
#include <exception>  // for terminate()

template<typename T>
class [[nodiscard]] ResultTask {
 public:
  // customization points:
  struct promise_type {
    T result{};                            // value from co_return

    void return_value(const auto& value) { // reaction to co_return
      result = value;                      // - store value locally
    }

    auto get_return_object() {
      return std::coroutine_handle<promise_type>::from_promise(*this);
    }
    auto initial_suspend() { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    auto final_suspend() noexcept { return std::suspend_always{}; }
  };
 private:
  std::coroutine_handle<promise_type> hdl;  // native coroutine handle

 public:
  // constructors and destructor:
  // - no copying or moving is supported
  ResultTask(auto h) : hdl{h} { }
  ~ResultTask() { if (hdl) hdl.destroy(); }
  ResultTask(const ResultTask&) = delete;
  ResultTask& operator=(const ResultTask&) = delete;

  // API:
  // - resume() to resume the coroutine
  bool resume() const {
    if (!hdl || hdl.done()) {
      return false;    // nothing (more) to process
    }
    hdl.resume();      // RESUME
    return !hdl.done();
  }

  // - getResult() to get the last value from co_yield
  T getResult() const {
    return hdl.promise().result;
  }
};

