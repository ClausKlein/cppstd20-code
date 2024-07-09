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

#pragma once

#include <iostream>

class Awaiter {
 public:
  bool await_ready() const noexcept {
    std::cout << "   await_ready()\n";
    return false;      // do suspend
  }

  void await_suspend(auto /* hdl */) const noexcept {
    std::cout << "   await_suspend()\n";
  }

  void await_resume() const noexcept {
    std::cout << "   await_resume()\n";
  }
};

