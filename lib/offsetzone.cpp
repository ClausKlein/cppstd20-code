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


#include "offsetzone.hpp"
#include <iostream>

int main()
{
  using namespace std::literals;  // for h and min suffix

  // timezone with 3:45 offset:
  OffsetZone p3_45{3h + 45min};

  // convert now to timezone with offset:
  auto now = std::chrono::system_clock::now();
  std::chrono::zoned_time<decltype(now)::duration, OffsetZone*> zt{&p3_45, now};

  std::cout << "UTC:    " << zt.get_sys_time() << '\n';
  std::cout << "+3:45:  " << zt.get_local_time() << '\n';
  std::cout << zt << '\n';
}

