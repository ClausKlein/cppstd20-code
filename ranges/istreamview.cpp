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
#include <sstream>
#include <ranges>
 
void print(std::ranges::input_range auto&& coll)
{
  for (const auto& elem : coll) { 
    std::cout << elem << "  ";
  }
  std::cout << '\n';
}

int main()
{
  std::string s{"2 4 6 8 Motorway 1977 by Tom Robinson"};

  std::istringstream mystream1{s};
  std::ranges::istream_view<std::string> vs{mystream1};
  print(vs);

  std::istringstream mystream2{s};
  auto vi = std::views::istream<int>(mystream2);
  print(vi);
}

