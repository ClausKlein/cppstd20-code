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
#include <atomic>
#include <semaphore>
using namespace std::literals;     // for duration literals

int main()
{
  char actChar = 'a';              // character value iterating endless from 'a' to 'z' 
  std::mutex actCharMx;            // mutex to access actChar

  // limit the availability of threads with a ticket system:
  std::atomic<int> maxTicket{0};   // maximum requested ticket no
  std::atomic<int> actTicket{0};   // current allowed ticket no

  // create and start a pool of numThreads threads:
  constexpr int numThreads = 10;
  std::vector<std::jthread> threads;
  for (int idx = 0; idx < numThreads; ++idx) {
    threads.push_back(std::jthread{[&, idx] (std::stop_token st) {
                                     while (!st.stop_requested()) {
                                       // get next character value:
                                       char val;
                                       {
                                         std::lock_guard lg{actCharMx};
                                         val = actChar++;
                                         if (actChar > 'z') actChar = 'a';
                                       }

                                       // request a ticket to process it and wait until enabled:
                                       int myTicket{++maxTicket};
                                       int act = actTicket.load();
                                       while (act < myTicket) {
                                         actTicket.wait(act);
                                         act = actTicket.load();
                                       }

                                       // print the character value 10 times:
                                       for (int i = 0; i < 10; ++i) {
                                         std::cout.put(val).flush();
                                         auto dur = 20ms * ((idx % 3) + 1);
                                         std::this_thread::sleep_for(dur);
                                       }

                                       // done, so enable next ticket:
                                       ++actTicket;
                                       actTicket.notify_all();
                                     }
                                   }});                       
  }

  // enable and disable threads in the thread pool:
  auto adjust = [&, oldNum = 0] (int newNum) mutable {
                  actTicket += newNum - oldNum;            // enable/disable tickets
                  if (newNum > 0) actTicket.notify_all();  // wake up waiting threads
                  oldNum = newNum;
                };

  for (int num : {0, 3, 5, 2, 0, 1}) {
    std::cout << "\n====== enable " << num << " threads" << std::endl;  
    adjust(num);
    std::this_thread::sleep_for(2s);
  }

  for (auto& t : threads) {   // request all threads to stop (join done when leaving scope)
    t.request_stop();
  }
}

