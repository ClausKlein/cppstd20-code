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
#include <array>
#include <algorithm>   // for std::fill_n()
#include <vector>
#include <format>
#include <random>
#include <thread>
#include <atomic>      // for std::atomic_ref<>
using namespace std::literals;  // for duration literals

int main()
{
  // create and initialize an array of integers with the value 100:
  std::array<int, 1000> values;
  std::fill_n(values.begin(), values.size(), 100);
  
  // initialize a common stop token for all threads:
  std::stop_source allStopSource;
  std::stop_token allStopToken{allStopSource.get_token()};

  // start multiple threads concurrently decrementing the value:
  std::vector<std::jthread> threads;
  for (int i = 0; i < 9; ++i) {
    threads.push_back(std::jthread{
      [&values] (std::stop_token st) {
         // initialize random engine to generate an index:
         std::mt19937 eng{std::random_device{}()};
         std::uniform_int_distribution distr{0, int(values.size()-1)};

         while (!st.stop_requested()) {
           // compute the next index:
           int idx = distr(eng);

           // enable atomic access to the value with the index:
           std::atomic_ref val{values[idx]};

           // and use it:
           --val;
           if (val <= 0) {
             std::cout << std::format("index {} is zero\n", idx);
           }
         }
      },
      allStopToken  // pass the common stop token
    });
  }

  // after a while/event request to stop all threads:
  std::this_thread::sleep_for(0.5s);
  std::cout << "\nSTOP\n";
  allStopSource.request_stop();
  //...
}

