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

auto getColl()
{
  return std::vector<std::string>{"you", "don't", "fool", "me"};
}

int main()
{
  std::ranges::owning_view v1 = getColl();    // view owning a vector of strings
  auto v2 = std::views::all(getColl());       // ditto
  static_assert(std::same_as<decltype(v1), decltype(v2)>);

  // iterate over drop view of owning view of vector<string>:
  for (const auto& elem : getColl() | std::views::drop(1)) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

