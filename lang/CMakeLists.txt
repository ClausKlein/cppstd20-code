set(cxx_sources
  add.cpp
  capturepack.cpp
  #XXX conceptnttp.cpp
  coord.cpp
  designated.cpp #NOTE: std::format used
  explicitwrapper.cpp
  lambdaconsteval.cpp
  lambdahash.cpp
  maxvalue.cpp
  #XXX nttpdouble.cpp
  #XXX nttpdouble2.cpp
  nttplambda.cpp
  nttpstring.cpp
  nttpstruct.cpp
  nttpstruct2.cpp
  #-Winfinite-recursion spacecompat.cpp
  tmplauto.cpp
  #TODO 
  valorcoll.cpp
)

foreach(source ${cxx_sources})
    string(REGEX REPLACE "\.cpp$" "" program ${source})
    add_executable(${program} ${program}.cpp)
    set_target_properties(${program} PROPERTIES CXX_STANDARD 20)
    add_test(NAME ${program} COMMAND ${program})
endforeach()

