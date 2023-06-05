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
#include <map>

int CoroPrioDefVal = 10;
enum class CoroPrioRequest {same, less, more, def};

class CoroPrioScheduler;

class [[nodiscard]] CoroPrioTask {
 public:
  struct promise_type;
  using CoroHdl = std::coroutine_handle<promise_type>;
 private:
  CoroHdl hdl;                              // native coroutine handle
  friend class CoroPrioScheduler;           // give access to the handle
 public:
  struct promise_type {
    CoroPrioScheduler* schedPtr = nullptr;  // each task knows its scheduler:

    auto get_return_object() { return CoroHdl::from_promise(*this); }
    auto initial_suspend() { return std::suspend_always{}; }
    void unhandled_exception() { std::terminate(); }
    void return_void() { }
    auto final_suspend() noexcept { return std::suspend_always{}; }

    auto await_transform(CoroPrioRequest);  // deal with co_await for a CoroPrioRequest 
  };

  // constructor and destructor:
  CoroPrioTask(CoroHdl h) : hdl{h} { }
  ~CoroPrioTask() { if (hdl) hdl.destroy(); }

  // move-only type:
  CoroPrioTask(const CoroPrioTask&) = delete;
  CoroPrioTask& operator=(const CoroPrioTask&) = delete;
  CoroPrioTask(CoroPrioTask&& ct)
   : hdl{ct.hdl} {
       ct.hdl = nullptr;
  }
  CoroPrioTask& operator=(CoroPrioTask&& ct) {
    if (this != &ct) {
      hdl = ct.hdl;
      ct.hdl = nullptr;
    }
    return *this;
  }
};

class CoroPrioScheduler
{
  std::multimap<int, CoroPrioTask> tasks;  // all tasks sorted by priority
 public:
  CoroPrioScheduler() = default;

  void start(CoroPrioTask&& task) {
    // store scheduler in coroutine state:
    task.hdl.promise().schedPtr = this;
    // schedule coroutine with a default priority:
    tasks.emplace(CoroPrioDefVal, std::move(task));
  }

  bool resumeNext() {
    // find next task with valid handle:
    if (tasks.empty()) return false;
    auto taskPos = tasks.begin();
    auto hdl = taskPos->second.hdl;
    while (!hdl || hdl.done()) {
      ++taskPos;
      if (taskPos == tasks.end()) {
        return false;   // nothing (more) to process
      }
      hdl = taskPos->second.hdl;
    }
    // resume that task:
    hdl.resume();              // RESUME
    if (hdl.done()) {
      tasks.erase(taskPos);
    }
    return !tasks.empty();
  }

  bool changePrio(CoroPrioTask::CoroHdl hdl, CoroPrioRequest pr) {
    for (auto pos = tasks.begin(); pos != tasks.end(); ++pos) {
      if (hdl == pos->second.hdl) {
        int newPrio = pos->first;
        switch (pr) {
          case CoroPrioRequest::same: break;
          case CoroPrioRequest::less: ++newPrio; break;
          case CoroPrioRequest::more: --newPrio; break;
          case CoroPrioRequest::def: newPrio = CoroPrioDefVal; break;
        }
        // if prio changed, update key of scheduled task:
        if (pos->first != newPrio) {
          auto nh = tasks.extract(pos);
          nh.key() = newPrio;
          tasks.insert(std::move(nh));
        }
        return true;
      }
    }
    return false;  // hdl not found
  }
};

inline auto CoroPrioTask::promise_type::await_transform(CoroPrioRequest pr) {  // deal with co_await CoroPrio
  auto _hdl = CoroPrioTask::CoroHdl::from_promise(*this);
  schedPtr->changePrio(_hdl, pr);
  return std::suspend_always{};
}

