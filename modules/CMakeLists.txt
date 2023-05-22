if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wno-unused-command-line-argument)
endif()

# FIXME(CK): unused? person1.cppm

#
# module with inline interface only
#
add_library(mod0)
target_sources(mod0 PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod0.cppm)
set_target_properties(mod0 PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod0 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(mod0main mod0main.cpp)
target_link_libraries(mod0main mod0)
add_test(NAME mod0main COMMAND mod0main)

#
# module with implementation:
# If you are using CMake to generate your Visual Studio solutions,
# remove the module implementation sources from the CXX_MODULES FILE_SET.
# You are using a module file extension like .ixx or .cppm for the module implementation source file,
# change the file extension to a non-module file extension like .cpp!
#
add_library(mod1)
target_sources(
  mod1
  PRIVATE mod1/mod1io.cpp mod1/mod1price.cpp
  PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod1/mod1.cppm
)
set_target_properties(mod1 PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
target_link_libraries(mod1 PUBLIC fmt::fmt)
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod1 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(testmod1 mod1/testmod1.cpp)
target_link_libraries(testmod1 mod1)
add_test(NAME testmod1 COMMAND testmod1)

#
# module with one internal partition
#
add_library(mod2)
target_sources(
  mod2
  PRIVATE mod2/mod2price.cpp
  PUBLIC FILE_SET
         cxx_modules
         TYPE
         CXX_MODULES
         FILES
         mod2/mod2.cppm
         mod2/mod2order.cppm
)
set_target_properties(mod2 PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod2 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(testmod2 mod2/testmod2.cpp)
target_link_libraries(testmod2 mod2)
add_test(NAME testmod2 COMMAND testmod2)

#
# module with internal partitions
#
add_library(mod3)
target_sources(
  mod3
  PRIVATE mod3/mod3price.cpp mod3/mod3io.cpp
  PUBLIC FILE_SET
         cxx_modules
         TYPE
         CXX_MODULES
         FILES
         mod3/mod3.cppm
         mod3/mod3customer.cppm
         mod3/mod3order.cppm
)
set_target_properties(mod3 PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
target_link_libraries(mod3 PUBLIC fmt::fmt)
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod3 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(testmod3 mod3/testmod3.cpp)
target_link_libraries(testmod3 mod3)
add_test(NAME testmod3 COMMAND testmod3)
