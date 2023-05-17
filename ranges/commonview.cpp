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
#include <string>
#include <list>
#include <vector>
#include <ranges>

void print(std::ranges::input_range auto&& coll)
{
  for (const auto& elem : coll) { 
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::list<std::string> coll{"You're", "my", "best", "friend"};

  auto tv = coll | std::views::take(3);
  static_assert(!std::ranges::common_range<decltype(tv)>);
  // could not initialize a container by passing begin and end of the view

  std::ranges::common_view vCommon1{tv};
  static_assert(std::ranges::common_range<decltype(vCommon1)>);

  auto tvCommon = coll | std::views::take(3) | std::views::common;
  static_assert(std::ranges::common_range<decltype(tvCommon)>);

  std::vector<std::string> coll2{tvCommon.begin(), tvCommon.end()};  // OK
  print(coll);
  print(coll2);
}

