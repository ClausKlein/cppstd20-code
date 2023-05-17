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
#include <ranges>

void print(std::ranges::input_range auto&& coll)
{
  if (coll.empty()) {
    std::cout << "<empty>\n";
  }
  else {
    for (const auto& elem : coll) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
  }
}

int main()
{
  std::ranges::empty_view<double> ev0;     // empty view of double
  auto ev1 = std::views::empty<int>;       // empty view of int

  print(ev0);
  print(ev1);
}

