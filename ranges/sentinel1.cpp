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

  // iterate over the range of the begin of rawString and its end:
  // NOLINTNEXTLINE(readability-qualified-auto)
  for (auto pos = rawString; pos != NullTerm{}; ++pos) {
    std::cout << ' ' << *pos;
  }
  std::cout << '\n';

  // call range algorithm with iterator and sentinel:
  std::ranges::for_each(rawString,   // begin of range
                        NullTerm{},  // end is null terminator
                        [] (char c) {
                          std::cout << ' ' << c;
                        });
  std::cout << '\n';
}

