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
#include <unordered_set>

class Customer
{
  std::string name;
 public:
  Customer(std::string n)
   : name{std::move(n)} {
  }
  Customer(const char* n)
   : name{n} {
  }
  //...
  [[nodiscard]] std::string getName() const {
    return name;
  }
  bool operator== (const Customer& c) const {
    return name == c.name;
  }
  //...
};

int main()
{
  // create hash table with user-defined hash function:
  std::unordered_set<Customer,
                     decltype([] (const Customer& c) {
                                return std::hash<std::string>{}(c.getName());
                              })> coll;  // OK since C++20

  coll.insert({std::string("Tom"), std::string("Andrea"), std::string("Sam")});
  coll.insert({"Kim", "Hans", "Sarah", "Bill"});

  for (const auto& c : coll) {
    std::cout << c.getName() << '\n';
  }
}

