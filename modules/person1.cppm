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


module;
#include <iostream>
#include <string>

export module ModPerson;   // THE module interface

class Person {             // note: \IBnot exported
   std::string name;
 public:
   Person(std::string n) 
    : name{std::move(n)} {
   }
   std::string getName() const {
     return name;
   }
};

std::ostream& operator<< (std::ostream& strm, const Person& p)
{
  return strm << p.getName();
}

export Person getPerson(std::string s) {
  return Person{s};
}

