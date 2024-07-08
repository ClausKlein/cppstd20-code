cmake_minimum_required(VERSION 3.28.4...3.30)

#---------------------------------------------------------------------------------------
# Compiler config
#---------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#=============================
project(samples LANGUAGES CXX)
#=============================

include(cmake/options.cmake)

# option(COMPILER_WARNINGS_ARE_ERRORS "To be pedantic! ;-)" ON)
# if(COMPILER_WARNINGS_ARE_ERRORS)
#   include(cmake/WarningsAsErrors.cmake)
# endif()

# ---- Setup default project_options ----

# cmake-format: off
project_options(
  # PREFIX ${PROJECT_NAME}
  ENABLE_CACHE
  #NO! ENABLE_CLANG_TIDY
  ${ENABLE_COVERAGE}
  ${OPTION_ENABLED_SANITIZER}
  #XXX ENABLE_SANITIZER_ADDRESS
  #XXX ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
  #XXX ENABLE_SANITIZER_THREAD
  #XXX ENABLE_SANITIZER_MEMORY
  #TODO: WARNINGS_AS_ERRORS
)
# cmake-format: on

CPMAddPackage("gh:TheLartians/Format.cmake@1.8.0")
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.11.0")

CPMAddPackage(
  NAME fmt
  GIT_TAG 11.0.1
  GITHUB_REPOSITORY fmtlib/fmt
  EXCLUDE_FROM_ALL NO
  SYSTEM YES
  OPTIONS "FMT_MODULE ON"
)
target_disable_clang_tidy(fmt)

target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

enable_testing()

# ---- Setup experimental cmake C++20 module support ----

# see https://releases.llvm.org/15.0.0/projects/libcxx/docs/ReleaseNotes.html
#XXX add_compile_options(-fexperimental-library)
#XXX add_link_options(-lc++experimental)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.28.4")
  set(CMAKE_CXX_SCAN_FOR_MODULES 1)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set(CMAKE_CXX_SCAN_FOR_MODULES 0)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14.1.0)
  add_subdirectory(modules)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 17.0.1)
  add_subdirectory(modules)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
  add_subdirectory(modules)
else()
  message(WARNING "Compiler ${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION} is not supported!")
endif()

if(NOT APPLE)
  add_subdirectory(coro)
endif()

if(NOT LINUX)
  add_subdirectory(comptime)
  if(NOT APPLE)
    add_subdirectory(format)
    add_subdirectory(ranges)
  endif()
endif()

add_subdirectory(lang)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_subdirectory(lib)
endif()

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

include(CPack)
include(cmake/AddUninstallTarget.cmake)
