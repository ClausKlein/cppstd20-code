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
#include <ranges>

void print(std::ranges::input_range auto&& coll)
{
  for (const auto& elem : coll) { 
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::ranges::single_view<double> sv0;             // single view double 0.0
  std::ranges::single_view sv1{42};                 // single_view<int> with int 42 

  auto sv2 = std::views::single('x');               // single_view<char>
  auto sv3 = std::views::single("ok");              // single_view<const char*>
  std::ranges::single_view<std::string> sv4{"ok"};  // single view with string "ok"

  print(sv0);
  print(sv1);
  print(sv2);
  print(sv3);
  print(sv4);
  print(std::ranges::single_view{42});
}

