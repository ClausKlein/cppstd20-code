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


#include "tracknew.hpp"
#include <iostream>
#include <string>
#include <coroutine>
#include <exception>  // for terminate()

// coroutine interface to deal with a simple task
// - providing resume() to resume it
class CoroTask {
 public:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;          // native coroutine handle

 public:
  struct promise_type {
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

  // constructor and destructor:
  CoroTask(auto h) : hdl{h} { }
  ~CoroTask() { if (hdl) hdl.destroy(); }

  // don't copy or move:
  CoroTask(const CoroTask&) = delete;
  CoroTask& operator=(const CoroTask&) = delete;

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


CoroTask coro(int max)
{
  for (int val = 1; val <= max; ++val) {
    std::cout << "    coro(" << max << "): " << val << '\n';
    co_await std::suspend_always{};
  }
}

CoroTask coroStr(int max, std::string s)
{
  for (int val = 1; val <= max; ++val) {
    std::cout << "    coroStr(" << max << ", " << s << "): " << '\n';
    co_await std::suspend_always{};
  }
}


int main()
{
  TrackNew::trace();
  TrackNew::reset();

  coro(3);                             // initialize temporary coroutine
  coroStr(3, "hello");                 // initialize temporary coroutine

  auto coroTask = coro(3);             // initialize coroutine
  std::cout << "coro() started\n";
  while (coroTask.resume()) {          // RESUME
    std::cout << "coro() suspended\n";
  }
  std::cout << "coro() done\n";
}

