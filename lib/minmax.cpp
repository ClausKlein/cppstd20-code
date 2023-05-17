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

int main()
{
  std::vector coll{0, 8, 15, 47, 11};

  std::cout << std::ranges::min(coll) << '\n';
  std::cout << std::ranges::max(coll) << '\n';
  auto [min, max] = std::ranges::minmax(coll);
  std::cout << min << ' ' << max << '\n';
}

