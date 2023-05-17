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

std::locale getLocale()
{
  // try to use German locale:
#ifdef _MSC_VER
  const char* nameDE = "deu_deu.1252";
#else
  const char* nameDE = "de_DE";
#endif
  try {
    return std::locale{nameDE};       // create German locale
  }
  catch (const std::exception& e) {
    std::cerr << "EXCEPTION: " << e.what() << '\n';
    std::cerr << " '" << nameDE << "' not supported\n";
    return std::locale{""};
  }
}

int main()
{
  // initialize locale:
  std::locale loc = getLocale();

  // use locale to print floating-point values:
  std::cout << std::format(loc, "{0} {0:L}\n", 1000.7);  // 1000.7 1.000,7
}

