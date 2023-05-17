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
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <semaphore>
using namespace std::literals;  // for duration literals

int main()
{
  std::queue<char> values;  // queue of values
  std::mutex valuesMx;      // mutex to protect access to the queue

  // initialize a queue with multiple sequences from 'a' to 'z':
  // - no mutex because no other thread is running yet
  for (int i = 0; i < 1000; ++i) {
    values.push(static_cast<char>('a' + (i % ('z'-'a'))));
  }
  
  // create a pool of numThreads threads:
  // - limit their availability with a semaphore (initially none available):
  constexpr int numThreads = 10;
  std::counting_semaphore<numThreads> enabled{0};

  // create and start all threads of the pool:
  std::vector<std::jthread> pool;
  for (int idx = 0; idx < numThreads; ++idx) {
    std::jthread t{[idx, &enabled, &values, &valuesMx] (std::stop_token st) {
                      while (!st.stop_requested()) {
                        // request thread to become one of the enabled threads:
                        enabled.acquire();

                        // get next value from the queue:
                        char val;
                        {
                          std::lock_guard lg{valuesMx};
                          val = values.front();
                          values.pop();
                        }

                        // print the value 10 times:
                        for (int i = 0; i < 10; ++i) {
                          std::cout.put(val).flush();
                          auto dur = 130ms * ((idx % 3) + 1);
                          std::this_thread::sleep_for(dur);
                        }

                        // remove thread from the set of enabled threads:
                        enabled.release();
                      }
                    }};
    pool.push_back(std::move(t));
  }

  std::cout << "== wait 2 seconds (no thread enabled)\n" << std::flush;  
  std::this_thread::sleep_for(2s);

  // enable 3 concurrent threads:
  std::cout << "== enable 3 parallel threads\n" << std::flush;  
  enabled.release(3);
  std::this_thread::sleep_for(2s);

  // enable 2 more concurrent threads:
  std::cout << "\n== enable 2 more parallel threads\n" << std::flush;  
  enabled.release(2); 
  std::this_thread::sleep_for(2s);

  // Normally we would run forever, but let's end the program here:
  std::cout << "\n== stop processing\n" << std::flush;  
  for (auto& t : pool) {
    t.request_stop();
  }
}

