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

void print (const auto& coll)
{
  for (const auto& elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::vector coll{1, 2, 3, 4, 5, 6, 7, 8};

  print(coll);

  // shift one element to the front (returns new end):
  std::shift_left(coll.begin(), coll.end(), 1);
  print(coll);

  // shift three elements to the back (returns new begin):
  auto newbeg = std::shift_right(coll.begin(), coll.end(), 3);
  print(coll);
  print(std::ranges::subrange{newbeg, coll.end()});
}

