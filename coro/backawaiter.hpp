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

template<typename Hdl>
class BackAwaiter {
  Hdl hdl = nullptr;   // coroutine handle saved from await_suspend() for await_resume()
 public:
  BackAwaiter() = default;

  bool await_ready() const noexcept {
    return false;                    // do suspend
  }

  void await_suspend(Hdl h) noexcept {
    hdl = h;                         // save handle to get access to its promise
  }

  auto await_resume() const noexcept {
    return hdl.promise().backValue;  // return back value stored in the promise
  }
};

