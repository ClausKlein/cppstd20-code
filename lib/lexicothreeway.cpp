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

std::ostream& operator<< (std::ostream& strm, std::strong_ordering val)
{
  if (val < 0) return strm << "less";
  if (val > 0) return strm << "greater";
  return strm << "equal";
}

int main()
{
  std::vector v1{0, 8, 15, 47, 11};
  std::vector v2{0, 15, 8};

  auto r1 = std::lexicographical_compare(v1.begin(), v1.end(),
                                         v2.begin(), v2.end());

  auto r2 = std::lexicographical_compare_three_way(v1.begin(), v1.end(),
                                                   v2.begin(), v2.end());
  std::cout << "r1: " << r1 << '\n';
  std::cout << "r2: " << r2 << '\n';
}



