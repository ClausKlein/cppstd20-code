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
  using namespace std::literals;    // for min, h, y suffixes

  try {
    // initialize today as current local date:
    auto localNow = chr::current_zone()->to_local(chr::system_clock::now());
    chr::year_month_day today{chr::floor<chr::days>(localNow)};
    std::cout << "today: " << today << '\n';

    // for each first Monday of all months of the current year:
    auto first = today.year() / 1 / chr::Monday[1];
    for (auto d = first; d.year() == first.year(); d += chr::months{1}) {
      // print out the date:
      std::cout << d << '\n';

      // init and print 18:30 local time of those days:
      auto tp{chr::local_days{d} + 18h + 30min};                     // no timezone
      std::cout << "  tp:      " << tp << '\n';

      // apply this local time to the current timezone:
      chr::zoned_time timeLocal{chr::current_zone(), tp};            // local time
      std::cout << "  local:   " << timeLocal << '\n';

      // print out date with other timezones:
      chr::zoned_time timeUkraine{"Europe/Kiev", timeLocal};         // Ukraine time
      chr::zoned_time timeUSWest{"America/Los_Angeles", timeLocal};  // Pacific time
      std::cout << "  Ukraine: " << timeUkraine << '\n';
      std::cout << "  Pacific: " << timeUSWest << '\n';
    }
  }
  catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << '\n';
  }
}

