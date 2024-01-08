if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wno-unused-command-line-argument)
endif()

# FIXME(CK): unused? person1.cppm

add_executable(modsimple)
target_sources(
  modsimple
  PRIVATE main.cxx
  PRIVATE FILE_SET CXX_MODULES
          # BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
          FILES importable.cxx
)
target_compile_features(modsimple PUBLIC cxx_std_20)
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(modsimple PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_test(NAME modsimple COMMAND modsimple)

#
# module with inline interface only
#
add_library(mod0 STATIC)
target_sources(mod0 PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod0.cppm)
target_compile_features(mod0 PUBLIC cxx_std_20)
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
# cmake-format: off
target_sources(
  mod1
  PRIVATE mod1/mod1io.cpp mod1/mod1price.cpp
  PUBLIC FILE_SET cxx_modules1
         TYPE CXX_MODULES
         # BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/mod1
         FILES mod1/mod1.cppm
)
# cmake-format: on
target_compile_features(mod1 PUBLIC cxx_std_20)
target_link_libraries(mod1 PUBLIC fmt::fmt)
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod1 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(testmod1 mod1/testmod1.cpp)
target_link_libraries(testmod1 mod1)
add_test(NAME testmod1 COMMAND testmod1)

#
# module with one internal partition
# see too:
# https://learn.microsoft.com/en-us/cpp/build/reference/internal-partition?view=msvc-170
#
add_library(mod2 STATIC)
# cmake-format: off
target_sources(
  mod2
  PRIVATE mod2/mod2price.cpp
  PUBLIC FILE_SET cxx_modules2
         TYPE CXX_MODULES
         # BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/mod2
         FILES
         mod2/mod2.cppm
         mod2/mod2order.cppm # internal partition
)
# cmake-format: on
target_compile_features(mod2 PUBLIC cxx_std_20)
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod2 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(testmod2 mod2/testmod2.cpp)
target_link_libraries(testmod2 mod2)
add_test(NAME testmod2 COMMAND testmod2)

#
# module with partitions
#
add_library(mod3 SHARED)
# cmake-format: off
target_sources(
  mod3
  PRIVATE mod3/mod3price.cpp mod3/mod3io.cpp
  PUBLIC FILE_SET cxx_modules3
         TYPE CXX_MODULES
         # BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/mod3
         FILES
         mod3/mod3.cppm
         mod3/mod3customer.cppm # interface partition
         mod3/mod3order.cppm # internal partition
)
# cmake-format: on
target_compile_features(mod3 PUBLIC cxx_std_20)
target_link_libraries(mod3 PUBLIC fmt::fmt)
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod3 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()
add_executable(testmod3 mod3/testmod3.cpp)
target_link_libraries(testmod3 mod3)
add_test(NAME testmod3 COMMAND testmod3)

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

install(TARGETS modsimple)

# cmake-format: off
install(
  TARGETS mod3 # TODO(CK): mod2 mod1
  EXPORT CXXModules
  # RUNTIME # Following options apply to runtime artifacts.
  #         COMPONENT Runtime
  # LIBRARY # Following options apply to library artifacts.
  #         COMPONENT Runtime #
  #         NAMELINK_COMPONENT Development
  # ARCHIVE # Following options apply to archive artifacts.
  #         COMPONENT Development
  #         DESTINATION lib/static
  # FILE_SET cxx_modules1
  #         COMPONENT Development
  #         DESTINATION lib/cxx/miu
  # FILE_SET cxx_modules2
  #         COMPONENT Development
  #         DESTINATION lib/cxx/miu
  FILE_SET cxx_modules3
          COMPONENT Development
          DESTINATION lib/cxx/miu
  CXX_MODULES_BMI
          COMPONENT Development
          DESTINATION lib/cxx/bmi
)
# cmake-format: on

install(
  EXPORT CXXModules
  NAMESPACE mymodules::
  DESTINATION lib/cmake/mod3
  FILE mod3-targets.cmake
  CXX_MODULES_DIRECTORY mod3-cxx-modules
)

file(
  WRITE "${CMAKE_CURRENT_BINARY_DIR}/mod3-config.cmake"
  "include(\"\${CMAKE_CURRENT_LIST_DIR}/mod3-targets.cmake\")
set(\${CMAKE_FIND_PACKAGE_NAME}_FOUND 1)
"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mod3-config.cmake" DESTINATION "lib/cmake/mod3")
