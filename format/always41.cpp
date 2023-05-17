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


#include "always41.hpp"
#include "formatalways41.hpp"
#include <iostream>

int main()
{
  try {
    Always41 val;
    std::cout << val.getValue() << '\n';
    std::cout << std::format("Value: {}\n", val); 
    std::cout << std::format("Twice: {0} {0}\n", val); 
    std::cout << std::format("With width: '{:7}'\n", val); 
    std::cout << std::format("With width: '{:f}'\n", val); 
  }
  catch (std::format_error& e) {
    std::cerr << "Format Error: " << e.what() << std::endl;
  }
}

