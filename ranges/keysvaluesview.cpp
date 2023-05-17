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
#include <unordered_map>
#include <ranges>
#include <numbers>    // for math constants
#include <algorithm>  // for sort()

void print(std::ranges::input_range auto&& coll)
{
  for (const auto& elem : coll) { 
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::unordered_map<std::string, double> coll{
      {"pi", std::numbers::pi},
      {"e", std::numbers::e},
      {"golden-ratio", std::numbers::egamma},
      {"euler-constant", std::numbers::phi},
  };

  print(std::ranges::keys_view<decltype(std::views::all(coll))>{coll});
  print(std::ranges::values_view<decltype(std::views::all(coll))>{coll});

  print(coll | std::views::keys);
  print(coll | std::views::values);
}

