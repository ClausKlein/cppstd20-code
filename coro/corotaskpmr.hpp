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
#include <cstddef>    // for std::byte
#include <array>
#include <memory_resource>

// coroutine interface to deal with a simple task
// - providing resume() to resume it
class [[nodiscard]] CoroTaskPmr {
  // provide 200k bytes as memory for all coroutines:
  inline static std::array<std::byte, 200'000> buf;
  inline static std::pmr::monotonic_buffer_resource
    monobuf{buf.data(), buf.size(), std::pmr::null_memory_resource()};
  inline static std::pmr::synchronized_pool_resource mempool{&monobuf};

 public:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;          // native coroutine handle

 public:
  struct promise_type {
    auto get_return_object() {       // init and return the coroutine interface
      return CoroTaskPmr{CoroHdl::from_promise(*this)};
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

    // define the way memory is allocated:
    void* operator new(std::size_t sz) {
      return mempool.allocate(sz);
    }
    void operator delete(void* ptr, std::size_t sz) {
      mempool.deallocate(ptr, sz);
    }
  };

  // constructor and destructor:
  CoroTaskPmr(auto h) : hdl{h} { }
  ~CoroTaskPmr() { if (hdl) hdl.destroy(); }

  // don't copy or move:
  CoroTaskPmr(const CoroTaskPmr&) = delete;
  CoroTaskPmr& operator=(const CoroTaskPmr&) = delete;

  // API to resume the coroutine
  // - returns whether there is still something to process
  bool resume() const {
    if (!hdl || hdl.done()) {
      return false;     // nothing (more) to process
    }
    hdl.resume();       // RESUME (blocks until suspended again or end)
    return !hdl.done();
  }
};

