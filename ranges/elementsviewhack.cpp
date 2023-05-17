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


// don't include <ranges> before "elementsview.hpp"
#include "elementsviewhack.hpp"
#include <iostream>
#include <vector>
#include <ranges>

void print(const auto& coll)
{
  std::cout << "coll:\n";
  for (const auto& elem : coll) {
    std::cout << "- " << elem << '\n';
  }
}

int main()
{
  Data d1{42, "truth"};
  std::vector<Data> coll{d1, Data{0, "null"}, d1};
  print(coll);
  print(coll | std::views::take(2));
  //FIXME: print(coll | std::views::elements<1>);
}

