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
  std::vector<std::tuple<int, std::string, double>> coll{
      {1, "pi", std::numbers::pi},
      {2, "e", std::numbers::e},
      {3, "golden-ratio", std::numbers::egamma},
      {4, "euler-constant", std::numbers::phi},
  };

  std::ranges::sort(coll, std::less{}, 
                    [](const auto& e) {return std::get<2>(e);});
  print(std::ranges::elements_view<decltype(std::views::all(coll)), 1>{coll});
  print(coll | std::views::elements<2>);
}

