cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

project(aoc-cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_CCACHE "Use ccache if available" ON)
if(USE_CCACHE)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  endif()
endif()

include(CTest)

add_definitions(-ggdb3)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-std=c++14)

add_subdirectory(src)
