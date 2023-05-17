cmake_minimum_required(VERSION 3.26)

## use ccache if found
find_program(CCACHE_EXECUTABLE ccache HINTS /usr/local/bin /opt/local/bin)
if(CCACHE_EXECUTABLE AND NOT CMAKE_TOOLCHAIN_FILE)
    message(STATUS "use ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXECUTABLE}" CACHE PATH "ccache" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#=============================
project(samples LANGUAGES CXX)
#=============================

#---------------------------------------------------------------------------------------
# Compiler config
#---------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(COMPILER_WARNINGS_ARE_ERRORS "To be pedantic! ;-)" ON)
if(COMPILER_WARNINGS_ARE_ERRORS)
  include(cmake/WarningsAsErrors.cmake)
endif()

# Where to put all the RUNTIME targets when built.  This variable is used to
# initialize the RUNTIME_OUTPUT_DIRECTORY property on all the targets.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API 2182bf5c-ef0d-489a-91da-49dbc3090d2a)
set(CMake_TEST_CXXModules_UUID "a246741c-d067-4019-a8fb-3d16b0c9d1d3")
# Workaround for C++Modules: Missing module map flags in exported compile commands
# see https://gitlab.kitware.com/cmake/cmake/-/issues/24618
set(CMAKE_CXX_COMPILE_OBJECT "${CMAKE_CXX_COMPILE_OBJECT} @<OBJECT>.modmap")

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
                "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -E -x c++ <SOURCE>"
                " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
                " -fmodules-ts -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT> -fdep-format=trtbd"
                " -o <PREPROCESSED_SOURCE>"
  )
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG "-fmodules-ts -fmodule-mapper=<MODULE_MAP_FILE> -fdep-format=trtbd -x c++")

  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY};-checks=*,-llvmlibc-*,-fuchsia-*,-cppcoreguidelines-init-variables")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "clang")
  set(CMAKE_EXE_LINKER_FLAGS -lstdc++)
  # see https://releases.llvm.org/15.0.0/projects/libcxx/docs/ReleaseNotes.html
  add_compile_options(-fexperimental-library)
  add_link_options(-lc++experimental)
endif()

enable_testing()

add_subdirectory(comptime)
add_subdirectory(lang)
add_subdirectory(modules)
add_subdirectory(ranges)

