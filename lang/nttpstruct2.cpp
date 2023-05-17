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
#include <array>

constexpr int foo()
{
  return 42;
}

struct Lit {
  int x = foo();        // OK because foo() is constexpr
  int y;
  constexpr Lit(int i)  // OK because constexpr
   : y{i} {
  }
};

struct Data {
  int i;
  std::array<double,5> vals;
  Lit lit;
};

template<auto Obj>
void func()
{
  std::cout << typeid(Obj).name() << '\n';
}

int main()
{
  func<Data{42, {1, 2, 3}, 42}>();    // OK

  constexpr Data d2{1, {2}, 3};
  func<d2>();   
}

