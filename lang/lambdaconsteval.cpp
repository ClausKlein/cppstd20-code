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
  auto isPrime = [](int value) constexpr {
                   for (int i = 2; i <= value/2; ++i) {
                     if (value % i == 0) {
                       return false;
                     }
                   }
                   return value > 1;  // 0 and 1 are no prime numbers
                 };

  // local compile-time computation of Num prime numbers:
  auto primeNumbers = [isPrime] <int Num> () consteval {
                        std::array<int, Num> primes{};
                        int idx = 0;
                        for (int val = 1; idx < Num; ++val) {
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

