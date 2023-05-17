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
#include <vector>
#include <map>
#include <ranges>

int main()
{
  namespace vws = std::views;

  // map of composers (mapping their name to their year of birth):
  std::map<std::string, int> composers{
    {"Bach", 1685},
    {"Mozart", 1756},
    {"Beethoven", 1770},
    {"Tchaikovsky", 1840},
    {"Chopin", 1810},
    {"Vivaldi ", 1678},
  };

  // iterate over the names of the first three composers born since 1700:
  for (const auto& elem : composers
                           | vws::filter([](const auto& y) {   // since 1700
                                           return y.second >= 1700;
                                         })
                           | vws::take(3)                      // first three
                           | vws::keys                         // keys/names only
                           ) {
    std::cout << "- " << elem << '\n'; 
  }
}

