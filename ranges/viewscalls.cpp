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
#include <vector>
#include <ranges>
namespace vws = std::views;

int main()
{
  std::cout << std::boolalpha;

  std::vector<int> coll{ 8, 15, 7, 0, 9, 13, 6, 0, 8, 15, 6 };

  // define a view  t1 | t2 | f1 | t3 | f2  :
  auto vColl = coll
                | vws::transform([] (int i) {
                                    std::cout << " t1: " << i << '\n';
                                    return i;
                                 })
                | vws::transform([] (int i) {
                                    std::cout << "  t2: " << i << '\n';
                                    return i;
                                 })
                | vws::filter([] (int i) {
                                    bool ret = i % 3 == 0;
                                    std::cout << "   f1: " << i
                                              << " => " << ret;
                                    std::cout << (ret ? "\n" : "\n\n");
                                    return ret;
                              })
                | vws::transform([] (int i) {
                                    std::cout << "    t3: " << i << '\n';
                                    return i;
                                 })
                | vws::filter([] (int i) {
                                    bool ret = i % 2 == 0;
                                    std::cout << "     f2: " << i
                                              << " => " << ret;
                                    std::cout << (ret ? "\n" : "\n\n");
                                    return ret;
                              });

  // and use it:
  for (int i : vColl) {
    std::cout << "      => " << i << '\n' << '\n';
  }
}

