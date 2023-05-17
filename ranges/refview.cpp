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
#include <ranges>

void printByVal(std::ranges::input_range auto coll)   // NOTE: takes range by value
{
  for (const auto& elem : coll) { 
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::vector<std::string> coll{"love", "of", "my", "life"};

  printByVal(coll);                         // copies coll
  printByVal(std::ranges::ref_view{coll});  // pass coll by reference
  printByVal(std::views::all(coll));        // ditto (using a range adaptor)   
}

