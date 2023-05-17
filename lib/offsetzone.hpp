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

#pragma once

#include <chrono>
#include <iostream>
#include <type_traits>

class OffsetZone
{
  private:
    std::chrono::minutes offset;  // UTC offset
  public:
    explicit OffsetZone(std::chrono::minutes offs)
     : offset{offs} {
    }

    template<typename Duration>
    auto to_local(std::chrono::sys_time<Duration> tp) const {
      // define helper type for local time:
      using LT
       = std::chrono::local_time<std::common_type_t<Duration,
                                                    std::chrono::minutes>>;
      // convert to local time:
      return LT{(tp + offset).time_since_epoch()};
    }

    template<typename Duration>
    auto to_sys(std::chrono::local_time<Duration> tp) const {
      // define helper type for system time:
      using ST
       = std::chrono::sys_time<std::common_type_t<Duration,
                                                  std::chrono::minutes>>;
      // convert to system time:
      return ST{(tp - offset).time_since_epoch()};
    }

    template<typename Duration>
    auto get_info(const std::chrono::sys_time<Duration>& tp) const {
      return std::chrono::sys_info{};
    }
};

