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
#include <source_location>

void foo()
{
  auto sl = std::source_location::current(); 
  //...
  std::cout << "file:     " << sl.file_name() << '\n';
  std::cout << "function: " << sl.function_name() << '\n';
  std::cout << "line/col: " << sl.line() << '/' << sl.column() << '\n';
}

void bar(std::source_location sl = std::source_location::current())
{
  //...
  std::cout << "file:     " << sl.file_name() << '\n';
  std::cout << "function: " << sl.function_name() << '\n';
  std::cout << "line/col: " << sl.line() << '/' << sl.column() << '\n';
}

std::source_location myfunc()
{
  auto sl = std::source_location::current();
  //...
  return sl;
}

int main()
{
  foo();
  std::cout << "---\n";
  bar();
  std::cout << "---\n";
  std::vector<std::source_location> locs;
  //...
  locs.push_back(myfunc());
  //...
  for (const auto& loc : locs) {
    std::cout << "called: '" << loc.function_name() << "'\n";
  }
}

