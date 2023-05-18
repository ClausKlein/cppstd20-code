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
#include <array>

int main()
{
  auto isPrime = [](size_t value) constexpr {
                   for (size_t i = 2; i <= value/2; ++i) {
                     if (value % i == 0) {
                       return false;
                     }
                   }
                   return value > 1;  // 0 and 1 are no prime numbers
                 };

  // local compile-time computation of Num prime numbers:
  auto primeNumbers = [isPrime] <size_t Num> () consteval {
                        std::array<size_t, Num> primes{};
                        size_t idx = 0;
                        for (size_t val = 1; idx < Num; ++val) {
                          if (isPrime(val)) {
                            primes[idx++] = val;
                          }
                        }
                        return primes;
                      };

  // init array with prime numbers:
  auto primes = primeNumbers.operator()<100>();

  for (auto v : primes) {
    std::cout << v << '\n';
  }
}

