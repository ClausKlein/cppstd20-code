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
#include <array>
#include <ranges>

void print(auto&& obj, int level = 0)
{
  if constexpr(std::ranges::input_range<decltype(obj)>) {
    std::cout << '[';
    for (const auto& elem : obj) { 
       print(elem, level+1);
    }
    std::cout << ']';
  }
  else { 
    std::cout << obj << ' ';
  }
  if (level == 0) std::cout << '\n';
}

int main()
{
  std::vector coll{1, 2, 3, 4, 1, 2, 3, 4};

  print(coll);                             // [1 2 3 4 1 2 3 4 ]
  print(std::ranges::split_view{coll, 2}); // [[1 ][3 4 1 ][3 4 ]]
  print(coll | std::views::split(3));       // [[1 2 ][4 1 2 ][4 ]]
  print(coll | std::views::split(std::array{4, 1})); // [[1 2 3 ][2 3 4 ]]
}

