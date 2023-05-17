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
#include <utility>
#include <ranges>

void printPairs(const auto& collOfPairs)
{
  for (const auto& elem : collOfPairs) {
    std::cout << elem.first << '/' << elem.second << ' ';  
  }
  std::cout << '\n';
}

int main()
{
  // initialize collection with pairs of int as elements:
  std::vector<std::pair<int,int>> coll{{1,9}, {9,1}, {2,2}, {4,1}, {2,7}};
  printPairs(coll);

  // function that yields the smaller of the two values in a pair:
  auto minMember = [] (std::pair<int,int>& elem) -> int& {
    return elem.second < elem.first ? elem.second : elem.first;
  };

  // increment the smaller of the two values in each pair element:
  for (auto&& member : coll | std::views::transform(minMember)) {
    ++member;
  }
  printPairs(coll);
}

