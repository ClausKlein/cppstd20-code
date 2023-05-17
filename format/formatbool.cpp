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
#include <locale>
#include <format>

// define facet for German bool names:
class GermanBoolNames : public std::numpunct_byname<char> {
 public:
  GermanBoolNames (const std::string& name)
   : std::numpunct_byname<char>(name) {
  }
 protected:
  virtual std::string do_truename() const {
    return "wahr";
  }
  virtual std::string do_falsename() const {
    return "falsch";
  }
};

int main()
{
  // create locale with German bool names:
  std::locale locBool{std::cin.getloc(),
                      new GermanBoolNames{""}};
  
  // use locale to print Boolean values:
  std::cout << std::format(locBool, "{0} {0:L}\n", false);  // false falsch
}

