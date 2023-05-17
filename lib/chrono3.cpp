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


#include <chrono>
#include <iostream>

int main()
{
  namespace chr = std::chrono;      // shortcut for std::chrono
  using namespace std::literals;    // for h, min, y suffixes

  // for each last of all months of 2021:
  chr::year_month_day first = 2021y / 1 / 31;
  for (auto d = first; d.year() == first.year(); d += chr::months{1}) {
    // print out the date:
    if (d.ok()) { 
      std::cout << d << ":\n";
    }
    else {
      // for months not having the 31st use the 1st of the next month: 
      auto d1 = d.year() / d.month() / 1 + chr::months{1};
      std::cout << d << ":\n";
    }

    // init and print 18:30 UTC of those days:
    auto tp{chr::sys_days{d} + 18h + 30min};
    std::cout << std::format(" We meet on {:%A %D at %R}\n", tp);
  }
}

