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
#include <format>
#include <bitset>
#include <bit>

int main()
{
  std::uint8_t i8 = 0b0000'1101; 
  std::cout
    << std::format("{0:08b} {0:3}\n", i8)                 // 00001101
    << std::format("{0:08b} {0:3}\n", std::rotl(i8, 2))   // 00110100
    << std::format("{0:08b} {0:3}\n", std::rotr(i8, 1))   // 10000110
    << std::format("{0:08b} {0:3}\n", std::rotr(i8, -1))  // 00011010
    << std::format("{}\n", std::countl_zero(i8))          // four leading zeros
    << std::format("{}\n", std::countr_one(i8))           // one trailing one
    << std::format("{}\n", std::popcount(i8))             // three ones
    << std::format("{}\n", std::has_single_bit(i8))       // false
    << std::format("{0:08b} {0:3}\n", std::bit_floor(i8)) // 00001000
    << std::format("{0:08b} {0:3}\n", std::bit_ceil(i8))  // 00010000
    << std::format("{}\n", std::bit_width(i8));           // 4
}

