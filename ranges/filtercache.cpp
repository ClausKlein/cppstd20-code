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
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::vector vec{1, 2, 3, 4};
  std::list   lst{1, 2, 3, 4};

  auto biggerThan2 = [](auto v){
    return v > 2;
  };

  auto vVec = vec | std::views::filter(biggerThan2);
  auto vLst = lst | std::views::filter(biggerThan2);

  // insert a new element at the front (=> 0 1 2 3 4)
  vec.insert(vec.begin(), 0);
  lst.insert(lst.begin(), 0);

  print(vVec);    // OK:  3 4
  print(vLst);    // OK:  3 4

  // insert more elements at the front (=> 98 99 0 -1 0 1 2 3 4)
  vec.insert(vec.begin(), {98, 99, 0, -1});
  lst.insert(lst.begin(), {98, 99, 0, -1});

  print(vVec);    // OOPS: -1 3 4
  print(vLst);    // OOPS: 3 4

  // creating a copy heals (except with random access):
  auto vVec2 = vVec;
  auto vLst2 = vLst;

  print(vVec2);   // OOPS: -1 3 4
  print(vLst2);   // OK: 98 99 3 4
}

