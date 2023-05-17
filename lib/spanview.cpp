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
#include <algorithm>
#include <span>

void print(std::ranges::input_range auto&& coll)
{
  for (const auto& elem : coll) {
    std::cout << '"' << elem << "\" ";
  }
  std::cout << '\n';
}

int main()
{
  std::vector<std::string> vec{"New York", "Tokyo", "Rio", "Berlin", "Sydney"};
  print(vec);

  // sort the three elements in the middle:
  std::ranges::sort(std::span{vec}.subspan(1, 3));
  print(vec);

  // print last three elements:
  print(std::span{vec}.last(3));
}

