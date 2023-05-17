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
#include <vector>
#include <array>
#include <ranges>
#include "printcoll.hpp"

int main()
{
  std::vector<std::string> rg1{"he", "hi", "ho"};
  std::vector<std::string> rg2{"---", "|", "---"};
  std::array coll{rg1, rg2, rg1};

  printColl(coll);                                       // ranges of ranges of strings
  //FIXME: printColl(std::ranges::join_view{coll});               // range of strings
  //FIXME: printColl(coll | std::views::join);                    // range of strings
  //FIXME: printColl(coll | std::views::join | std::views::join); // ranges of chars
}

