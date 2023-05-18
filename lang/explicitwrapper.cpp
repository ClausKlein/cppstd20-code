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


#include "wrapper.hpp"
#include <string>
#include <vector>

void printStringWrapper(const Wrapper<std::string>& /*unused*/) {
}
void printVectorWrapper(const Wrapper<std::vector<std::string>>& /*unused*/) {
}

int main()
{
  // implicit conversion from string literal to string:
  std::string s1{"hello"};
  std::string s2 = "hello";                       // OK
  Wrapper<std::string> ws1{"hello"};
  Wrapper<std::string> ws2 = "hello";             // OK
  printStringWrapper("hello");                    // OK

  // NO implicit conversion from size to vector<string>:
  std::vector<std::string> v1{42U};
  //XXX std::vector<std::string> v2 = 42U;              // ERROR: explicit
  Wrapper<std::vector<std::string>> wv1{42U};
  //XXX Wrapper<std::vector<std::string>> wv2 = 42U;    // ERROR: explicit
  //XXX printVectorWrapper(42U);                        // ERROR: explicit
}

