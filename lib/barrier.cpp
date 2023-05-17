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
#include <format>
#include <vector>
#include <thread>
#include <cmath>
#include <barrier>

int main()
{
  // initialize and print a collection of floating-point values: 
  std::vector values{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  // define a lambda function that prints all values
  // - NOTE: has to be noexcept to be used as barrier callback
  auto printValues = [&values] () noexcept{
                       for (auto val : values) {
                         std::cout << std::format(" {:<7.5}", val);
                       }
                       std::cout << '\n';
                     };
  // print initial values:
  printValues();
  
  // initialize a barrier that prints the values when all threads have done their computations:
  std::barrier allDone{int(values.size()),  // initial value of the counter
                       printValues};        // callback to call whenever the counter is 0

  // initialize a thread for each value to compute its square root in a loop:
  std::vector<std::jthread> threads;
  for (std::size_t idx = 0; idx < values.size(); ++idx) {
    threads.push_back(std::jthread{[idx, &values, &allDone] {
                                     // repeatedly:
                                     for (int i = 0; i < 5; ++i) {
                                       // compute square root:
                                       values[idx] = std::sqrt(values[idx]);
                                       // and synchronize with other threads to print values:
                                       allDone.arrive_and_wait();
                                     }
                                   }});                       
  }
  //...
}

