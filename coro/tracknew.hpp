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


#ifndef TRACKNEW_HPP
#define TRACKNEW_HPP

#include <new>
#include <cstdio>    // for printf()
#include <cstdlib>   // for malloc()
#include <string>
#include <iostream>

// track heap memory allocations
// - turn on with TrackNew::trace()
class TrackNew {
  inline static int numAlloc = 0;
  inline static int numFree = 0;
  inline static std::size_t sumSize = 0;
  inline static bool doTrace = false; // tracing enabled
  inline static bool inNew = false;   // don't track output inside new overloads
 public:
  // reset new/memory counters
  static void reset() {
    numAlloc = 0;
    numFree = 0;
    sumSize = 0;
  }

  // enable print output for each new:
  static void trace(bool b = true) {
    doTrace = b;
  }

  // print current state:
  static void status() {
    // don't use iostreams, because they allocate on Windows
    printf("*> %d mallocs for %d Bytes (with %d frees)\n",
           numAlloc, (int)sumSize, numFree);
  }

  // implementation of tracked allocation:
  static void* allocate(std::size_t size, const char* msg) {
    if (inNew) {
      return std::malloc(size);
    }
    inNew = true;
      ++numAlloc;
      sumSize += size;
      void* p = std::malloc(size);
      if (doTrace) {
        // don't use iostreams, because they allocate on Windows
        if (size > 0) {
          printf("%s #%d (%d Bytes) => %p (total: %d Bytes)\n",
                 msg, numAlloc, (int)size, (void*)p, (int)sumSize);
        }
        else {
          printf("%s #%d (no size) => %p (total: %d Bytes)\n",
                 msg, numAlloc, (void*)p, (int)sumSize);
        }
      }
    inNew = false;
    return p;
  }

  // implementation of tracked deallocation:
  static void deallocate(void* p, std::size_t size, const char* msg) {
    if (!p) return;
    // trace output might again allocate memory, so handle this the usual way:
    if (inNew) {
      std::free(p);
      return;
    }
    inNew = true;
      ++numFree;
      // track and trace the allocation:
      std::free(p);
      if (doTrace) {
        // don't use iostreams, because they allocate on Windows
        if (size > 0) {
          printf("%s (%d bytes) at %p\n", msg, (int)size, (void*)p);
        }
        else {
          printf("%s (no size) at %p\n", msg, (void*)p);
        }
      }
    inNew = false;
  }
};

void* operator new (std::size_t size) {
    return TrackNew::allocate(size, "::new");
}

void* operator new[] (std::size_t size) {
    return TrackNew::allocate(size, "::new[]");
}

void operator delete (void* p) noexcept {
    return TrackNew::deallocate(p, 0, "::delete");
}

void operator delete[] (void* p) noexcept {
    return TrackNew::deallocate(p, 0, "::delete[]");
}

void operator delete (void* p, std::size_t size) noexcept {
    return TrackNew::deallocate(p, size, "::delete");
}

void operator delete[] (void* p, std::size_t size) noexcept {
    return TrackNew::deallocate(p, size, "::delete[]");
}

#endif // TRACKNEW_HPP

