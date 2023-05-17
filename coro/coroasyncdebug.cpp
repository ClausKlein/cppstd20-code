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
#include <list>
#include <utility>     // for std::exchange()
#include <functional>  // for std::function
#include <coroutine>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore>
#include <functional>
#include <cassert>
#include <syncstream> // for std::osyncstream
#include <chrono>
using namespace std::literals;


// true:  enable debug output
// false: disable debug output
constexpr bool syncOutDebug = true;

inline auto syncOut(std::ostream& strm = std::cout) {
  return std::osyncstream{strm};
}

inline auto coutDebug() {
  if constexpr (syncOutDebug) {
    return std::osyncstream{std::cout};
  }
  else {
    struct devnullbuf : public std::streambuf {
      // basic output primitive without any print statement:
      int_type overflow (int_type c) {
        return c;
      }
    };
    static devnullbuf devnull;
    return std::ostream{&devnull};
  }
}


class CoroPool;

class [[nodiscard]] CoroPoolTask
{
  friend class CoroPool;
 public:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;
  int coroId = -1;
 public:
  struct promise_type {
    inline static std::atomic<int> maxId = 0;
    int id = ++maxId;
    CoroPool* poolPtr = nullptr;   // if not null, lifetime is controlled by pool
    CoroHdl contHdl = nullptr;     // coro that awaits this coro
  
    CoroPoolTask get_return_object() noexcept {
      return CoroPoolTask{CoroHdl::from_promise(*this)};
    }
    auto initial_suspend() const noexcept { return std::suspend_always{}; }
    void unhandled_exception() noexcept { std::exit(1); }
    void return_void() noexcept {}

    auto final_suspend() const noexcept {
      struct FinalAwaiter {
        bool await_ready() const noexcept { return false; }
        std::coroutine_handle<> await_suspend(CoroHdl h) noexcept {
          if (h.promise().contHdl) {
            coutDebug() << "= coro" << h.promise().id << " finally suspended"
                        << " => continue with coro" << h.promise().contHdl.promise().id << std::endl; 
            return h.promise().contHdl;    // resume continuation
          }
          else {
            coutDebug() << "= coro" << h.promise().id << " finally suspended" << std::endl; 
            return std::noop_coroutine();  // no continuation
          }  
        }
        void await_resume() noexcept {
          coutDebug() << "= await_resume()" << std::endl; 
        }
      };
      return FinalAwaiter{};  // AFTER suspended, resume continuation if there is one
    }
  };

  explicit CoroPoolTask(CoroHdl handle)
   : hdl{handle}, coroId{hdl.promise().id} {
    assert(hdl);
    coutDebug() << "= CoroPoolTask() for coro" << hdl.promise().id << std::endl;
  }
  ~CoroPoolTask() {
    if (hdl && !hdl.promise().poolPtr) {
      // task was not passed to pool:
      coutDebug() << "= DESTROY coro" << hdl.promise().id << " by task (not by pool)"
                  << " on thread " << std::this_thread::get_id() << std::endl;
      hdl.destroy();
    }
  }
  CoroPoolTask(const CoroPoolTask&) = delete;
  CoroPoolTask& operator= (const CoroPoolTask&) = delete;
  CoroPoolTask(CoroPoolTask&& t)
   : hdl{t.hdl} {
      coutDebug() << "= MOVE coro" << hdl.promise().id << std::endl;
      t.hdl = nullptr;
  }
  CoroPoolTask& operator= (CoroPoolTask&&) = delete;

  // Awaiter for:  co_await task()
  // - queues the new coro in the pool
  // - sets the calling coro as continuation
  struct CoAwaitAwaiter {
    CoroHdl newHdl;
    bool await_ready() const noexcept { return false; }
    void await_suspend(CoroHdl awaitingHdl) noexcept;  // see below
    void await_resume() noexcept {}
  };
  auto operator co_await() noexcept {
    coutDebug() << "= OPERATOR co_await() for coro" << hdl.promise().id << std::endl;
    coutDebug() << "= POOL takes ownership of coro" << hdl.promise().id << std::endl;
    return CoAwaitAwaiter{std::exchange(hdl, nullptr)}; // pool takes ownership of hdl
  }
};

class CoroPool
{
 private:
  std::list<std::jthread> threads;         // list of threads
  std::list<CoroPoolTask::CoroHdl> coros;  // queue of scheduled coros
  std::mutex corosMx;
  std::condition_variable_any corosCV;
  std::atomic<int> numCoros = 0;           // counter for all coros owned by the pool

 public:
  explicit CoroPool(int num) {
    // start pool with num threads:
    for (int i = 0; i < num; ++i) {
      std::jthread worker_thread{[this](std::stop_token st) {
                                   threadLoop(st);
                                 }};
      threads.push_back(std::move(worker_thread));
    }
  }

  ~CoroPool() {
    for (auto& t : threads) {  // request stop for all threads
      t.request_stop();
    }
    for (auto& t : threads) {  // wait for end of all threads
      t.join();
    }
    for (auto& c : coros) {    // destroy remaining coros
      coutDebug() << "= DESTROY coro" << c.promise().id << " by POOL destructor" << std::endl;
      c.destroy();
    }
  }

  CoroPool(CoroPool&) = delete;
  CoroPool& operator=(CoroPool&) = delete;

  void runTask(CoroPoolTask&& coroTask) noexcept {
    coutDebug() << "= RUN task coro" << coroTask.hdl.promise().id
                << " by pool" << std::endl;
    coutDebug() << "= POOL takes ownership of coro" << coroTask.hdl.promise().id << std::endl;
    runCoro(std::exchange(coroTask.hdl, nullptr)); // pool takes ownership of hdl
  }

  // runCoro(): let pool run (and control lifetime of) coroutine
  // called from:
  // - pool.runTask(CoroPoolTask)
  // - co_await task()
  void runCoro(CoroPoolTask::CoroHdl coro) noexcept {
    coutDebug() << "== runCoro() for coro" << coro.promise().id
                << " = INCR numCoros" << std::endl;
    ++numCoros;
    coro.promise().poolPtr = this;  // disables destroy in CoroPoolTask
    {
      std::scoped_lock lock(corosMx);
      coros.push_front(coro);       // queue coro
      corosCV.notify_one();         // and let one thread resume it
    }
  }

  void threadLoop(std::stop_token st) {
    while (!st.stop_requested()) {
      // get next coro task from the queue:
      CoroPoolTask::CoroHdl coro;
      {
        coutDebug() << "      --->>> WAIT by " << std::this_thread::get_id() << std::endl;
        std::unique_lock lock(corosMx);
        if (!corosCV.wait(lock, st, [&] {
                                      return !coros.empty();
                                    })) {
          coutDebug() << "      --->>> STOP for " << std::this_thread::get_id() << std::endl;
          return;  // stop requested
        }
        coro = coros.back();
        coros.pop_back();
      }

      // resume it:
      auto id = coro.promise().id;
      coutDebug() << "      ***>>> RESUME coro" << id
                  << " by " << std::this_thread::get_id() << std::endl;
      coro.resume();  // RESUME
      if (coro.done()) {
        coutDebug() << "      ***<<< SUSPEND coro" << id
                    << " DONE by " << std::this_thread::get_id() << std::endl;
      }
      else {
        coutDebug() << "      ***<<< SUSPEND coro" << id
                    << " by " << std::this_thread::get_id() << std::endl;
      }

      // NOTE: The coro initially resumed in this thread might NOT be the coro finally called.
      //       If a coroMain co_await's a coroSub, then
      //       the thread that finally resumed coroSub resumes coroMain as its continuation.
      //       => After this resumption this coro and SOME continuations MIGHT be done
      std::function<void(CoroPoolTask::CoroHdl)> destroyDone;
      destroyDone = [&destroyDone, this](auto hdl) { 
                      // coutDebug() << "= destroyDone() for coro" << hdl.promise().id << std::endl;
                      if (hdl && hdl.done()) {
                        auto nextHdl = hdl.promise().contHdl;
                        coutDebug() << "= DESTROY coro" << hdl.promise().id << " by POOL" << std::endl;
                        hdl.destroy();         // destroy done handle
                        --numCoros;            // adjust total number of coros
                        destroyDone(nextHdl);  // do it for all done continuations
                      }
                    };
      destroyDone(coro);      // recursively destroy done coros
      numCoros.notify_all();  // wake-up any waiting waitUntilNoCoros() 

      // sleep a bit to force that another thread is used next:
      std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
  }

  void waitUntilNoCoros() {
    int num = numCoros.load();
    coutDebug() << "\nwaitUntilNoCoros(): " << num << " left" << std::endl;
    while (num > 0) {
      numCoros.wait(num);  // wait for notification that numCoros changed the value
      num = numCoros.load();
      coutDebug() << "\nwaitUntilNoCoros(): " << num << " left" << std::endl;
    }
  }

  void syncWait(CoroPoolTask&& task) {
    std::binary_semaphore taskDone{0};
    auto makeWaitingTask = [&]() -> CoroPoolTask {
      coutDebug() << "  waitingTask(): co_await task" << std::endl;
      co_await task;
      coutDebug() << "  waitingTask(): co_await SignalDone{}" << std::endl;
      struct SignalDone {
        std::binary_semaphore& taskDoneRef;
        bool await_ready() { return false; }
        bool await_suspend(std::coroutine_handle<>) {
          taskDoneRef.release();  // signal task is done
          return false;           // do not suspend at all
        }
        void await_resume() { }
      };
      co_await SignalDone{taskDone};
      coutDebug() << "  waitingTask(): done" << std::endl;
    };
    coutDebug() << "\nsyncWait(): makeWaitingTask()" << std::endl;
    auto t = makeWaitingTask();
    coutDebug() << "\nsyncWait(): runTask()" << std::endl;
    runTask(std::move(t));
    taskDone.acquire();
    coutDebug() << "\nsyncWait(): done" << std::endl;
    corosCV.notify_one();       // let one thread resume it
  }
};

// CoroPoolTask awaiter for:  co_await task()
// - queues the new coro in the pool
// - sets the calling coro as continuation
void CoroPoolTask::CoAwaitAwaiter::await_suspend(CoroHdl awaitingHdl) noexcept
{
  assert(newHdl);
  coutDebug() << "= RUN coro" << newHdl.promise().id << " via co_await "
              << "(suspend coro" << awaitingHdl.promise().id << " for it)" << std::endl;
  assert(awaitingHdl.promise().poolPtr);
  assert(!newHdl.promise().contHdl);
  newHdl.promise().contHdl = awaitingHdl;
  awaitingHdl.promise().poolPtr->runCoro(newHdl);
}


CoroPoolTask print(std::string id, std::string msg)
{
  syncOut() << "    > " << id <<  " print: " << msg << "   on thread: " << std::this_thread::get_id() << std::endl;
  co_return;
}

CoroPoolTask runAsync(std::string id)
{
  syncOut() << "===== " << id << " start        on thread: " << std::this_thread::get_id() << std::endl;

/*
  co_await print(id + "a", "start");
  syncOut() << "===== " << id << " resume       on thread " << std::this_thread::get_id() << std::endl;

  co_await print(id + "b", "end  ");
  syncOut() << "===== " << id << " resume       on thread " << std::this_thread::get_id() << std::endl;
*/
  syncOut() << "===== " << id << " done" << std::endl;
  co_return;
}

int main()
{
  // init pool of coroutine threads:
  syncOut() << "**** main() on thread " << std::this_thread::get_id() << std::endl;
  CoroPool pool{4};

  // start main coroutine and run it in coroutine pool:
  syncOut() << "runTask(runAsync(0))" << std::endl;
  CoroPoolTask t0 = runAsync("0");
  pool.runTask(std::move(t0));

  syncOut() << "\n**** t1 = runAsync(1)" << std::endl;
  auto t1 = runAsync("1");
  syncOut() << "\n**** syncWait(t1)" << std::endl;
  pool.syncWait(std::move(t1));

  // start other coroutines:
  for (int i = 0; i < 3; ++i) {
    syncOut() << "runTask(runAsync(" << i + 2 << "))" << std::endl;
    CoroPoolTask t = runAsync(std::to_string(i + 2));
    pool.runTask(std::move(t));
  }

  // wait until all coroutines are done:
  syncOut() << "\n**** waitUntilNoCoros()" << std::endl;
  pool.waitUntilNoCoros();

  syncOut() << "\n**** main() done" << std::endl;
}

