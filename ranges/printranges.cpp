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
#include <list>
#include <ranges>

void print(auto&& rg)
{
  for (const auto& elem : rg) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::vector vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list   lst{1, 2, 3, 4, 5, 6, 7, 8, 9};

  print(vec | std::views::take(3));                      // OK
  print(vec | std::views::drop(3));                      // OK

  print(lst | std::views::take(3));                      // OK
  print(lst | std::views::drop(3));                      // OK
  for (const auto& elem : lst | std::views::drop(3)) {   // OK
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  auto isEven = [] (const auto& val) {
    return val % 2 == 0;
  };
  print(vec | std::views::filter(isEven));               // OK
}

