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


#include <iostream>
#include <coroutine>
#include <exception>  // for terminate()

// coroutine interface to deal with a simple task
// - providing resume() to resume it
class CoroTask {
 public:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;            // native coroutine handle
 public:
  // special promise type for passed coroutine interface
  struct promise_type {
    promise_type(int, CoroTask& ct) {  // init passed coroutine interface
      ct.hdl = CoroHdl::from_promise(*this);
    }
    void get_return_object() {         // nothing to do anymore
    }  

    auto initial_suspend() {           // initial suspend point
      return std::suspend_always{};    // - suspend immediately
    }
    void unhandled_exception() {       // deal with exceptions
      std::terminate();                // - terminate the program
    }
    void return_void() {               // deal with the end or with return;
    }
    auto final_suspend() noexcept {    // final suspend point
      return std::suspend_always{};    // - suspend at the end
    }
  };

  // constructors and destructor:
  CoroTask() : hdl{} {                 // default constructor: no handle yet
  }
  ~CoroTask() {
    if (hdl) hdl.destroy();            // destroy coroutine handle if there is one
  }
  // don't copy or move:
  CoroTask(const CoroTask&) = delete;
  CoroTask& operator=(const CoroTask&) = delete;

  // API to resume the coroutine
  // - returns whether there is still something to process
  bool resume() const {
    if (!hdl || hdl.done()) {
      return false;     // nothing (more) to process
    }
    hdl.resume();       // RESUME
    return !hdl.done();
  }
};

template<>
struct std::coroutine_traits<void, int, CoroTask&>
{
  using promise_type = CoroTask::promise_type;
};

void coro(int max, CoroTask&)
{
  std::cout << "CORO " << max << " start\n";

  for (int val = 1; val <= max; ++val) {
    // print next value:
    std::cout << "CORO " << val << '/' << max << '\n';

    co_await std::suspend_always{};     // SUSPEND
  }

  std::cout << "CORO " << max << " end\n";
}

int main()
{
  CoroTask coroTask;  // create coroutine interface without coroutine

  // start coroutine:
  coro(3, coroTask);  // init and store coroutine in the interface created
  std::cout << "--- coro() started\n";

  // loop to resume the coroutine until it is done:
  while (coroTask.resume()) {           // RESUME
    std::cout << "--- coro() suspended\n";
  }

  std::cout << "--- coro() done\n";
}

