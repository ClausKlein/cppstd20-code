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
#include <string_view>
#include <vector>
#include <algorithm>
 
void print(std::string_view msg, auto beg, auto end)
{
   std::cout << msg;
   for(auto pos = beg; pos != end; ++pos) {
      std::cout << ' ' << *pos;
   }
   std::cout << '\n';
}

int main()
{
    std::vector inColl{1, 2, 3, 4, 5, 6, 7};
    std::vector outColl{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};    

    auto result = std::ranges::transform(inColl, outColl.begin(),
                                         [] (auto val) {
                                           return val*val;
                                         });
 
    print("processed in:", inColl.begin(), result.in);
    print("rest of in:  ", result.in, inColl.end());
    print("written out: ", outColl.begin(), result.out);
    print("rest of out: ", result.out, outColl.end());
}

