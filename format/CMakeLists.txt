if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(cxx_sources formatperf.cpp color.cpp)
else()

  set(cxx_sources
      #XXX always40.cpp
      #XXX always41.cpp
      #XXX always42.cpp
      #XXX always42inherit.cpp
      #XXX color.cpp
      formatbool.cpp formatgerman.cpp formatperf.cpp
  )
endif()

add_tests(cxx_sources)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_link_libraries(formatperf PRIVATE fmt::fmt)
  target_link_libraries(formatbool PRIVATE fmt::fmt)
  target_link_libraries(formatgerman PRIVATE fmt::fmt)
endif()
