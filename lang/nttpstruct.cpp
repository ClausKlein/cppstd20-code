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
#include <cmath>
#include <cassert>

struct Tax {
  double value;

  constexpr Tax(double v)
   : value{v} {
      assert(v >= 0 && v < 1);
  }

  friend std::ostream& operator<< (std::ostream& strm, const Tax& t) {
    return strm << t.value;
  }
};

template<Tax Vat>
int addTax(int value)
{
  return static_cast<int>(std::round(value * (1 + Vat.value))); 
}

int main()
{
  constexpr Tax tax{0.19};
  std::cout << "tax: " << tax << '\n';

  std::cout << addTax<tax>(100) << '\n';
  std::cout << addTax<tax>(4199) << '\n';
  std::cout << addTax<Tax{0.07}>(1950) << '\n';
}

