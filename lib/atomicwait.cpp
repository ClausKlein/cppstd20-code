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
#include <atomic>
using namespace std::literals;

int main()
{
  std::atomic<int> aVal{0};

  // reader:
  std::jthread tRead{[&] {
                       int lastX = aVal.load();
                       while (lastX >= 0) {
                         aVal.wait(lastX);
                         std::cout << "=> x changed to " << lastX << std::endl;
                         lastX = aVal.load();
                       }
                       std::cout << "READER DONE" << std::endl;
                    }};

  // writer:
  std::jthread tWrite{[&] {
                        for (int newVal : { 17, 34, 3, 42, -1}) {
                          std::this_thread::sleep_for(5ns);
                          aVal = newVal;
                          aVal.notify_all();
                        }
                     }};
  //...
}

