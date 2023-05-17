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
#include <vector>
#include <ranges>
#include <coroutine>        // for \Tstd::suspend_always{}
#include "resulttask.hpp"   // for ResultTask

ResultTask<double> average(auto coll)
{
  double sum = 0;
  for (const auto& elem : coll) {
    std::cout << "  process " << elem << '\n';
    sum = sum + elem;
    co_await std::suspend_always{};        // SUSPEND
  }
  co_return sum / std::ranges::ssize(coll);  // return resulting average
}

int main()
{
  std::vector values{0, 8, 15, 47, 11, 42};

  // start coroutine:
  auto task = average(std::views::all(values));

  // loop to resume the coroutine until all values have been processed:
  std::cout << "resume()\n";
  while (task.resume()) {                // RESUME
    std::cout << "resume() again\n";
  }

  // print return value of coroutine:
  std::cout << "result: " << task.getResult() << '\n';
}

