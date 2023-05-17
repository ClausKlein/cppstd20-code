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
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <span>

template<typename T, std::size_t Sz>
void printSpan(std::span<T, Sz> sp)
{
  for (const auto& elem : sp) {
    std::cout << '"' << elem << "\" ";
  }
  std::cout << '\n';
}

int main()
{
  std::vector<std::string> vec{"New York", "Tokyo", "Rio", "Berlin", "Sydney"};

  // define view to first 3 elements:
  std::span<const std::string> sp{vec.data(), 3};
  std::cout << "first 3:                   ";
  printSpan(sp);

  // sort elements in the referenced vector:
  std::ranges::sort(vec);
  std::cout << "first 3 after sort():      ";
  printSpan(sp);

  // insert a new element:
  // - must reassign the internal array of the vector if it reallocated new memory
  auto oldCapa = vec.capacity();
  vec.push_back("Cairo");
  if (oldCapa != vec.capacity()) {
    sp = std::span{vec.data(), 3};
  }
  std::cout << "first 3 after push_back(): ";
  printSpan(sp);

  // let span refer to the vector as a whole:
  sp = vec;
  std::cout << "all:    ";
  printSpan(sp);  

  // let span refer to the last five elements:
  sp = std::span{vec.end()-5, vec.end()};
  std::cout << "last 5: ";
  printSpan(sp);

  // let span refer to the last four elements:
  sp = std::span{vec}.last(4);
  std::cout << "last 4: ";
  printSpan(sp);
}

