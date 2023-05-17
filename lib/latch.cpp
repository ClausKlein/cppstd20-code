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
#include <thread>
#include <latch>
using namespace std::literals;  // for duration literals

void loopOver(char c) {
  // loop over printing the char c:
  for (int j = 0; j < c/2; ++j) {
    std::cout.put(c).flush();
    std::this_thread::sleep_for(100ms);
  }
}

int main()
{
  std::array tags{'.', '?', '8', '+', '-'};  // tags we have to perform a task for

  // initialize latch to react when all tasks are done:
  std::latch allDone{tags.size()};   // initialize countdown with number of tasks

  // start two threads dealing with every second tag:
  std::jthread t1{[tags, &allDone] {
                    for (unsigned i = 0; i < tags.size(); i += 2) {  // even indexes
                      loopOver(tags[i]);
                      // signal that the task is done:
                      allDone.count_down();  // atomically decrement counter of latch
                    }
                    //...
                  }};
  std::jthread t2{[tags, &allDone] {
                    for (unsigned i = 1; i < tags.size(); i += 2) {  // odd indexes
                      loopOver(tags[i]);
                      // signal that the task is done:
                      allDone.count_down();  // atomically decrement counter of latch
                    }
                    //...
                  }};
  //...
  // wait until all tasks are done:
  std::cout << "\nwaiting until all tasks are done\n";
  allDone.wait();                      // wait until counter of latch is zero
  std::cout << "\nall tasks done\n";   // note: threads might still run  
  //...
}

