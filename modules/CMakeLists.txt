set(cxx_sources mod0main.cpp)

add_library(mod0)
target_sources(
  mod0
  PUBLIC FILE_SET
         cxx_modules
         TYPE
         CXX_MODULES
         FILES
         mod0.cppm
)
add_executable(mod0main mod0main.cpp)
target_link_libraries(mod0main mod0)
add_test(NAME mod0main COMMAND mod0main)

