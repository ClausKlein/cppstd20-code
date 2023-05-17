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


#include <vector>
#include <array>
#include <ranges>
#include "printcoll.hpp"

void printConstColl(const auto& coll)
{
  printColl(coll);
}

int main()
{
  std::vector<int> rg1{1, 2, 3, 4};
  std::vector<int> rg2{0, 8, 15};
  std::vector<int> rg3{5, 4, 3, 2, 1, 0};
  std::array coll{rg1, rg2, rg3};

  printConstColl(coll);
  printConstColl(coll | std::views::join);   // ERROR

  auto collTx = [] (const auto& coll) { return coll; };
  auto coll2values = coll | std::views::transform(collTx);

  printConstColl(coll2values);
  printConstColl(coll2values | std::views::join);   // ERROR
}

