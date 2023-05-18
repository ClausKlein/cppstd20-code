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
#include <utility>   // for std::swap()
#include <concepts>  // for std::ranges::swap()

struct Foo {
  Foo() = default;
  ~Foo() = default;

  Foo(const Foo& /*unused*/) {
    std::cout << " COPY constructor\n";
  }

#if 0
  Foo(const Foo&& /*unused*/) {
    std::cout << " MOVE constructor\n";
  }
  Foo& operator=(const Foo&& /*unused*/) {
    std::cout << " MOVE assignment\n";
    return *this;
  }
#endif

  Foo& operator=(const Foo& /*unused*/) {
    std::cout << " COPY assignment\n";
    return *this;
  }

  void swap(Foo& /*unused*/) {
    std::cout << " efficient swap()\n";  // swaps pointers, no data
  }
};

void swap(Foo& a, Foo& b) {
  a.swap(b);
}

int main()
{
  Foo a;
  Foo b(a);
  a = b;

  std::cout << "--- std::swap()\n";
  std::swap(a, b);          // generic swap called

  std::cout << "--- swap() after using std::swap\n";
  using std::swap;
  swap(a, b);               // efficient swap called

  std::cout << "--- std::ranges::swap()\n";
  std::ranges::swap(a, b);  // efficient swap called
}

