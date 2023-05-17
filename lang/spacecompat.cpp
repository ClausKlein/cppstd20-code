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

class MyType {
 private:
  int value;
 public:
  MyType(int i)    // implicit constructor from int:
   : value{i} {
  }

  bool operator==(const MyType& rhs) const {
    return value == rhs.value;
  }
};

bool operator==(int i, const MyType& t) {
  return t == i;   // OK with C++17
}

int main()
{
  MyType x = 42;
  if (0 == x) {
    std::cout << "'0 == MyType{42}' works\n";
  }
}

