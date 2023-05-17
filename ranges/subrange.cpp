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
#include <unordered_map>
#include <ranges>
 
void printPairs(auto&& rg)
{
  for (const auto& [key, val] : rg) {
    std::cout << key << ':' << val << ' ';
  }
  std::cout << '\n';
}

int main()
{
  // English/German dictionary:
  std::unordered_multimap<std::string,std::string> dict = {
    {"strange", "fremd"},
    {"smart", "klug"},
    {"car", "Auto"},
    {"smart","raffiniert"},
    {"trait", "Merkmal"},
    {"smart", "elegant"},
  };
  
  // get begin and end of all elements with translation of "smart":
  auto [beg, end] = dict.equal_range("smart");

  // create subrange view to print all translations:
  printPairs(std::ranges::subrange(beg, end));
}

