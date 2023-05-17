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
#include <ranges>
namespace vws = std::views;

void print(const auto& coll)
{
  std::cout << "coll: ";
  for (int i : coll) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}
 
int main()
{
  std::vector<int> coll{1, 4, 7, 10, 13, 16, 19, 22, 25};

  // view for all even elements of coll:
  auto isEven = [] (auto&& i) { return i % 2 == 0; };
  auto collEven = coll | vws::filter(isEven);

  print(coll);

  // modify even elements in coll:
  for (int& i : collEven) {
    std::cout << " increment " << i << '\n';
    i += 1;    // ERROR: undefined behavior because filter predicate is broken
  }
  print(coll);

  // modify even elements in coll:
  for (int& i : collEven) {
    std::cout << " increment " << i << '\n';
    i += 1;    // ERROR: undefined behavior because filter predicate is broken
  }
  print(coll);
}

