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
#include <vector>
#include <ranges>
#include <cmath>   // for std::sqrt()

void print(std::ranges::input_range auto&& coll)
{
  for (const auto& elem : coll) { 
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::vector coll{1, 2, 3, 4, 1, 2, 3, 4, 1};

  print(coll);                                       // 1 2 3 4 1
  auto sqrt = [] (auto v) { return std::sqrt(v); };
  print(std::ranges::transform_view{coll, sqrt});    // 1 1.41421 1.73205 2 1
  print(coll | std::views::transform(sqrt));         // 1 1.41421 1.73205 2 1
}

