set(cxx_sources
  comptimestring.cpp #NOTE: std::format used
  consteval1.cpp
  #XXX consteval2.cpp
  constinit.cpp
  #FIXME fiasco.cpp
  isconsteval.cpp
  mergevalues.cpp
  mergevaluessz.cpp
  #XXX returnvector.cpp
  #TODO no main: truth.cpp
  vector.cpp
)

foreach(source ${cxx_sources})
    string(REGEX REPLACE "\.cpp$" "" program ${source})
    add_executable(${program} ${program}.cpp)
    set_target_properties(${program} PROPERTIES CXX_STANDARD 20)
    add_test(NAME ${program} COMMAND ${program})
endforeach()

