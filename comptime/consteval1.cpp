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

constexpr
bool isPrime(size_t value)
{
  for (size_t i = 2; i <= value/2; ++i) {
    if (value % i == 0) {
      return false;
    }
  }
  return value > 1;  // 0 and 1 are not prime numbers
}

template<size_t Num>
consteval
std::array<size_t, Num> primeNumbers()
{
  std::array<size_t, Num> primes{};
  size_t idx = 0;
  for (size_t val = 1; idx < Num; ++val) {
    if (isPrime(val)) {
      primes[idx++] = val;
    }
  }
  return primes;
}

int main()
{
  // init with prime numbers:
  auto primes = primeNumbers<100>();

  for (const auto v : primes) {
    std::cout << v << '\n';
  }
}

