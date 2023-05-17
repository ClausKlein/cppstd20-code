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
  std::uint16_t i16 = 0b0000'1101; 
  std::cout
    << std::format("{0:016b} {0:5}\n", i16)                  // 0000000000001101
    << std::format("{0:016b} {0:5}\n", std::rotl(i16, 2))    // 0000000000110100
    << std::format("{0:016b} {0:5}\n", std::rotr(i16, 1))    // 1000000000000110
    << std::format("{0:016b} {0:5}\n", std::rotr(i16, -1))   // 0000000000011010
    << std::format("{}\n", std::countl_zero(i16))            // 12 leading zeros
    << std::format("{}\n", std::countr_one(i16))             // 1 trailing one
    << std::format("{}\n", std::popcount(i16))               // 3 ones
    << std::format("{}\n", std::has_single_bit(i16))         // false
    << std::format("{0:016b} {0:5}\n", std::bit_floor(i16))  // 0000000000001000
    << std::format("{0:016b} {0:5}\n", std::bit_ceil(i16))   // 0000000000010000
    << std::format("{}\n", std::bit_width(i16));             // 4
}

