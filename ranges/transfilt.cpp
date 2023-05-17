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

int main()
{
  std::vector<int> coll{ 8, 15, 7, 0, 9 };

  // define a view:
  auto vColl = coll
                | vws::transform([] (int i) {
                                   std::cout << " trans: " << i << '\n';
                                   return -i;
                                 })
                | vws::filter([] (int i) {
                                std::cout << "  filt: " << i << '\n';
                                return i % 3 == 0;
                              });

  // and use it:
  std::cout << "*** coll | transform | filter:\n";
  for (int val : vColl) {
    std::cout << "val: " << val << "\n\n";
  }
}

