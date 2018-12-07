cmake_minimum_required(VERSION 3.1..3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_VERSION})
endif()

add_executable(d1p1 d1p1.cpp)
add_executable(d1p2 d1p2.cpp)
add_executable(d2p1 d2p1.cpp)
add_executable(d2p2 d2p2.cpp)

resource(d1.input)
resource(d2.input)

test(TARGET d1p1 INPUT d1.input)
test(TARGET d1p2 INPUT d1.input)
test(TARGET d2p1 INPUT d2.input)
test(TARGET d2p2 INPUT d2.input)
