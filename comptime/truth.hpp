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


#ifndef TRUTH_HPP
#define TRUTH_HPP

struct Truth {
  int value;
  Truth() : value{42} {  // ensure all objects are initialized with 42
  }
};

extern Truth theTruth;   // declare global object

#endif // TRUTH_HPP

