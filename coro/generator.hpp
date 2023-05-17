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
#include <cassert>    // for assert()

template<typename T>
class [[nodiscard]] Generator {
 public:
  // customization points:
  struct promise_type {
    T coroValue{};                  // last value from co_yield

    auto yield_value(T val) {        // reaction to co_yield
      coroValue = val;               // - store value locally
      return std::suspend_always{};  // - suspend coroutine
    }

    auto get_return_object() {
      return std::coroutine_handle<promise_type>::from_promise(*this);
    }
    auto initial_suspend() { return std::suspend_always{}; }
    void return_void() { }
    void unhandled_exception() { std::terminate(); }
    auto final_suspend() noexcept { return std::suspend_always{}; }
  };

 private:
  std::coroutine_handle<promise_type> hdl;  // native coroutine handle

 public:
  // constructors and destructor:
  Generator(auto h) : hdl{h} { }
  ~Generator() { if (hdl) hdl.destroy(); }

  // no copy or move supported:
  Generator(const Generator&) = delete;
  Generator& operator=(const Generator&) = delete;

  // API to resume the coroutine and access its values:
  // - iterator interface with begin() and end()
  struct iterator {
    std::coroutine_handle<promise_type> hdl;  // nullptr on end
    iterator(auto p) : hdl{p} {
    }
    void getNext() {
      if (hdl) {
        hdl.resume();        // RESUME
        if (hdl.done()) {
          hdl = nullptr;
        }
      }
    }
    int operator*() const {
      assert(hdl != nullptr);
      return hdl.promise().coroValue;
    }
    iterator operator++() {
      getNext();             // resume for next value
      return *this;
    }
    bool operator== (const iterator& i) const = default;
  };

  iterator begin() const {
    if (!hdl || hdl.done()) {
      return iterator{nullptr};
    }
    iterator itor{hdl};      // initialize iterator
    itor.getNext();          // resume for first value
    return itor;
  }

  iterator end() const {
    return iterator{nullptr};
  }
};

