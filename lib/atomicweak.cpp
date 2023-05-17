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
#include <thread>
#include <memory>               // includes <atomic> now
using namespace std::literals;  // for duration literals


int main()
{
  std::atomic<std::weak_ptr<int>> pShared;  // pointer to current shared value (if one exists)

  // loop to set shared value for some time:
  std::atomic<bool> done{false};
  std::jthread updates{[&] {
                         for (int i = 0; i < 10; ++i) {
                           {
                             auto sp = std::make_shared<int>(i);
                             pShared.store(sp);   // atomic update
                             std::this_thread::sleep_for(0.1s);
                           }
                           std::this_thread::sleep_for(0.1s);
                         }
                         done.store(true);
                       }};

  // loop to print shared value (if any):
  while (!done.load()) {
    if (auto sp = pShared.load().lock()) {  // atomic read
      std::cout << "shared: " << *sp << '\n';
    }
    else {
      std::cout << "shared: <no data>\n";
    }
    std::this_thread::sleep_for(0.07s);
  }
}

