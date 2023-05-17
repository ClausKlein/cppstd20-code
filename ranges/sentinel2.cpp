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
#include <compare>
#include <algorithm>  // for for_each()

struct NullTerm {
  bool operator== (auto pos) const {
    return *pos == '\0';  // end is where iterator points to \verb+'\0'+
  }
};

int main()
{
  const char* rawString = "hello world";

  // define a range of a raw string and a null terminator:
  std::ranges::subrange rawStringRange{rawString, NullTerm{}};

  // use the range in an algorithm: 
  std::ranges::for_each(rawStringRange,
                        [] (char c) {
                          std::cout << ' ' << c;
                        });
  std::cout << '\n';

  // range-based for loop also supports iterator/sentinel:
  for (char c : rawStringRange) {
    std::cout << ' ' << c;
  }
  std::cout << '\n';
}

