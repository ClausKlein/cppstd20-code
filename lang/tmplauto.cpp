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


#include <vector>
#include <ranges>

void addValInto(const auto& val, auto& coll)
{
  coll.insert(val);
}

template<typename Coll>   // Note: different order of template parameters
requires std::ranges::random_access_range<Coll>
void addValInto(const auto& val, Coll& coll)
{
  coll.push_back(val);
}

int main()
{
  std::vector<int> coll;
  //XXX addValInto(42, coll);   // ERROR: ambiguous
}

