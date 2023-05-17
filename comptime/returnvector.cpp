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


#include <vector>

constexpr auto returnVector()
{
  std::vector<int> v{0, 8, 15};
  v.push_back(42);
  //...

  return v;
}

constexpr auto returnVectorSize()
{
  auto coll = returnVector();
  return coll.size();
}

int main()
{
  constexpr auto coll = returnVector();   // ERROR
  constexpr auto tmp = returnVectorSize();  // OK
  //...
}

