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

void printStringWrapper(Wrapper<std::string>) {
}
void printVectorWrapper(Wrapper<std::vector<std::string>>) {
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
  std::vector<std::string> v1{42u};
  //XXX std::vector<std::string> v2 = 42u;              // ERROR: explicit
  Wrapper<std::vector<std::string>> wv1{42u};
  //XXX Wrapper<std::vector<std::string>> wv2 = 4u2;    // ERROR: explicit
  //XXX printVectorWrapper(42u);                        // ERROR: explicit
}

