set(cxx_sources
  commonview.cpp
  dropcache.cpp
  dropview.cpp
  #XXX dropwhilecache.cpp
  dropwhileview.cpp
  elementsview.cpp
  elementsviewhack.cpp
  emptyview.cpp
  #XXX filtercache.cpp
  filterview.cpp
  filttrans.cpp
  filttrans2.cpp
  iotaview.cpp
  istreamview.cpp
  #XXX joinconst.cpp
  joinview.cpp
  keysvaluesview.cpp
  keysview.cpp
  maxvalue2.cpp
  owningview.cpp
  #XXX printconst.cpp
  printranges.cpp
  rangesproj.cpp
  rangessort.cpp
  refview.cpp
  results.cpp
  reversecache.cpp
  reverseview.cpp
  sentinel1.cpp
  sentinel2.cpp
  sentinel3.cpp
  singleview.cpp
  splitview.cpp
  subrange.cpp
  subrangecounted.cpp
  takeview.cpp
  takewhileview.cpp
  transfilt.cpp
  transformref.cpp
  transformview.cpp
  valuesview.cpp
  viewscalls.cpp
  #XXX viewslazy.cpp
  viewspipe.cpp
  viewswrite.cpp
)

foreach(source ${cxx_sources})
    string(REGEX REPLACE "\.cpp$" "" program ${source})
    add_executable(${program} ${program}.cpp)
    set_target_properties(${program} PROPERTIES CXX_STANDARD 20)
    add_test(NAME ${program} COMMAND ${program})
endforeach()
