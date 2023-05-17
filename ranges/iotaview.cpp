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

void print(std::ranges::input_range auto&& coll)
{
  int num = 0;
  for (const auto& elem : coll) { 
    std::cout << elem << ' ';
    if (++num > 30) {  // print only up to 30 values:
      std::cout << "...";
      break;
    }
  }
  std::cout << '\n';
}

int main()
{
  std::ranges::iota_view<int> iv0;            // 0 1 2 3 ...
  print(iv0);
  
  std::ranges::iota_view iv1{-2};             // -2 -1 0 1 ...
  print(iv1);
  
  std::ranges::iota_view iv2{10, 20};         // 10 11 12 ... 19
  print(iv2);
  
  auto iv3 = std::views::iota(1);             // -2 -1 0 1 ...
  print(iv3);
  
  auto iv4 = std::views::iota('a', 'z'+1);    // a b c ... z
  print(iv4);
  
  std::vector coll{0, 8, 15, 47, 11};
  for (auto p : std::views::iota(coll.begin(), coll.end())) { // sequence of iterators
    std::cout << *p << ' ';                   // 0 8 15 47 11
  }
  std::cout << '\n';
}

