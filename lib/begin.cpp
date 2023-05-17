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
#include <cstdlib>
#include <filesystem>

// type with member begin():
struct MemberBegin {
  //...
  int* begin() const {
    std::cout << "MemberBegin::begin()\n";
    return new int{42};
  }
};

// type with global free-standing begin():
struct GlobalBegin {
  //...
};
int* begin(GlobalBegin) {
  std::cout << "::begin(GlobalBegin)\n";
  return new int{42};
}

// type with free-standing begin() in a namespace:
namespace ns {
  struct NsBegin {
    //...
  };

  int* begin(NsBegin) {
    std::cout << "ns::begin(NsBegin)\n";
    return new int{42};
  }
}

int main()
{
   MemberBegin m;
   GlobalBegin g;
   ns::NsBegin n;
   std::filesystem::directory_iterator dir{"."};

   // direct std::begin() doesn't always work:
   std::cout << "--- std::begin() direct:\n";
   {
     std::begin(m);            // OK: MemberBegin::begin()
     //std::begin(g);          // ERROR: begin(GlobalBegin) not found
     //std::begin(n);          // ERROR: nd::begin(ns::NsBegin) not found
     std::begin(s);            // OK: std::begin(NsStdBegin)
     //std::begin(dir);        // ERROR: doesn't work for filesystem iterators
   }

   // std::begin() with using declaration:
   std::cout << "--- using std::begin():\n";
   {
     using std::begin;
     begin(m);                 // OK: ::begin(m)
     begin(g);                 // OK: ::begin(g)
     begin(n);                 // OK: ns::begin(NsBegin)
     begin(dir);               // OK
   }

   // std::ranges::begin() works better:
   std::cout << "--- std::ranges::begin() direct:\n";
   {
     std::ranges::begin(m);    // OK: ::begin(m)
     std::ranges::begin(g);    // OK: ::begin(g)
     std::ranges::begin(n);    // OK: ns::begin(NsBegin)
     std::ranges::begin(dir);  // OK
   }

   // for std::ranges::begin() a using declaration doesn't change anything:
   std::cout << "--- using std::ranges::begin():\n";
   {
     using std::ranges::begin;
     begin(m);                 // OK: ::begin(m)
     begin(g);                 // OK: ::begin(g)
     begin(n);                 // OK: ns::begin(NsBegin)
     begin(dir);               // OK
   }
}


