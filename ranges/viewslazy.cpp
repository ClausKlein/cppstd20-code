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
#include <list>
#include <ranges>

void print(auto&& coll)
{
  for (const auto& elem : coll) {
    std::cout << ' ' << elem;
  }
  std::cout << '\n';
}

int main()
{
  std::vector vec{1, 2, 3, 4, 5};
  std::list lst{1, 2, 3, 4, 5};

  auto over2 = [](auto v) { return v > 2; };
  auto over2vec = vec | std::views::filter(over2);
  auto over2lst = lst | std::views::filter(over2);

  std::cout << "containers and elements over 2:\n";
  print(vec);               // OK:  1 2 3 4 5
  print(lst);               // OK:  1 2 3 4 5
  print(over2vec);          // OK:  3 4 5
  print(over2lst);          // OK:  3 4 5

  // modify underlying ranges:
  vec.insert(vec.begin(), {9, 0, -1});
  lst.insert(lst.begin(), {9, 0, -1});

  std::cout << "containers and elements over 2:\n";
  print(vec);               // vec now: 9 0 -1 1 2 3 4 5
  print(lst);               // lst now: 9 0 -1 1 2 3 4 5
  print(over2vec);          // OOPS:  -1 3 4 5
  print(over2lst);          // OOPS:  3 4 5

  // copying might eliminate caching:
  auto over2vec2 = over2vec;
  auto over2lst2 = over2lst;
  std::cout << "elements over 2 after copying the view:\n";
  print(over2vec2);         // OOPS:  -1 3 4 5
  print(over2lst2);         // OK:  9 3 4 5
}

