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
  auto now = std::chrono::system_clock::now();               // type is sys_time<>
  auto today = std::chrono::floor<std::chrono::days>(now);   // type is sys_days
  std::chrono::year_month_day ymd{today};
  std::chrono::hh_mm_ss hms{now - today};
  std::chrono::weekday wd{today};

  std::cout << "now:      " << now << '\n';
  std::cout << "today:    " << today << '\n';
  std::cout << "ymd:      " << ymd << '\n';
  std::cout << "hms:      " << hms << '\n';
  std::cout << "year:     " << ymd.year() << '\n';
  std::cout << "month:    " << ymd.month() << '\n';
  std::cout << "day:      " << ymd.day() << '\n';
  std::cout << "hours:    " << hms.hours() << '\n';
  std::cout << "minutes:  " << hms.minutes() << '\n';
  std::cout << "seconds:  " << hms.seconds() << '\n';
  std::cout << "subsecs:  " << hms.subseconds() << '\n';
  std::cout << "weekday:  " << wd << '\n';

  try {
    std::chrono::sys_info info{std::chrono::current_zone()->get_info(now)};
    std::cout << "timezone: " << info.abbrev << '\n';
  }
  catch (const std::exception& e) {
    std::cerr << "no timezone database: (" << e.what() << ")\n";
  }
}

