cmake_minimum_required(VERSION 3.1)

add_executable(dummy dummy.cpp)
coveralls_upload(program.dummy) # program doesn't matter
