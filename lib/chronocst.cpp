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
#include <chrono>
using namespace std::literals;

int main(int argc, char** argv)
{
  auto abbrev = argc > 1 ? argv[1] : "CST";

  auto day = std::chrono::sys_days{2021y/1/1};
  auto& db = std::chrono::get_tzdb();

  // print time and name of all timezones with abbrev:
  std::cout << std::chrono::zoned_time{"UTC", day}
            << " maps to these '" << abbrev << "' entries:\n";
  // iterate over all timezone entries:
  for (const auto& z : db.zones) {
    // and map to those using my passed (or default) abbreviation:
    if (z.get_info(day).abbrev == abbrev) {
      std::chrono::zoned_time zt{&z, day};
      std::cout << "  " << zt << "  " << z.name() << '\n';
    }
  }
}

