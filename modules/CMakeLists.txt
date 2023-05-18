if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wno-unused-command-line-argument)
endif()

add_library(mod0)
target_sources(mod0 PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES mod0.cppm)
set_target_properties(mod0 PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
if(CMAKE_SKIP_INSTALL_RULES AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_link_libraries(mod0 PUBLIC $<BUILD_INTERFACE:project_warnings project_options>)
endif()

add_executable(mod0main mod0main.cpp)
target_link_libraries(mod0main mod0)
add_test(NAME mod0main COMMAND mod0main)
