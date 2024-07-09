set(cxx_sources
    awaiter.cpp
    coreturn.cpp
    coro.cpp
    coro2.cpp
    #syncstream coroasync1.cpp
    #syncstream coroasync2.cpp
    #syncstream coroasyncdebug.cpp
    corocoro.cpp
    coromem.cpp
    #memory_resource coromempmr.cpp
    coroprio.cpp
    coroprio2.cpp
    cororange.cpp
    #XXX cororef.cpp
    corotrace.cpp
    corotraits.cpp
    coyield.cpp
    coyieldback.cpp
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  #FIXME(CK): AddressSanitizer: heap-use-after-free: list(APPEND cxx_sources corocorosub.cpp)
endif()

add_tests(cxx_sources)
