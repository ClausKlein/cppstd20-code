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
#include <algorithm>
#include <ranges>

void print(auto coll)
{
  std::cout << '[';
  for (const auto& elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << "]\n";
}

int main()
{
  std::vector<int> coll{25, -42, 2, 0, 122, -5, 7};  
  print(coll);

  // default sorting of the whole range/container:
  std::ranges::sort(coll);
  print(coll);

  // passing a sorting criterion:
  std::ranges::sort(coll,
                    [] (auto val1, auto val2) {
                      return std::abs(val1) < std::abs(val2);
                    });
  print(coll);

  // passing a transformation/projection:
  std::ranges::sort(coll,
                    std::less{},
                    [] (auto val) {
                      return std::abs(val);
                    });
  print(coll);

  // find the element where the square is 25:
  auto pos = std::ranges::find(coll, 25,                  // find element with value 25
                               [](auto x) {return x*x;}); // when it is squared
  if (pos != coll.end()) {
    std::cout << "first value with square 25: " << *pos << '\n';
  }
}

