cmake_minimum_required(VERSION 3.1)

option(USE_KCOV "Use kcov if available" ON)
if(USE_KCOV)
  find_program(KCOV_PROGRAM kcov)
  set(KCOV_ARGS "--exclude-pattern=/usr/include,thirdparty,/usr/lib")
  set(KCOV_REPORT_PATH "/tmp/aoc-cpp")
else()
  add_definitions(-O3)
endif()

function(resource FILE)
  configure_file("${FILE}" "${FILE}" COPYONLY)
endfunction()

function(coveralls_upload PROGRAM) # ARGN as list of args
  if(USE_KCOV AND KCOV_PROGRAM)
    if(TRAVIS_JOB_ID)
      add_test(NAME "coveralls-upload" COMMAND ${KCOV_PROGRAM} ${KCOV_ARGS} --coveralls-id=${TRAVIS_JOB_ID} ${KCOV_REPORT_PATH} "${PROGRAM}" ${ARGN})
    endif()
  endif()
endfunction()

function(test)
  set(args TARGET INPUT)
  cmake_parse_arguments(TEST "" "${args}" "" ${ARGN})
  if(USE_KCOV AND KCOV_PROGRAM)
    add_test(NAME ${TEST_TARGET} COMMAND ${CMAKE_SOURCE_DIR}/scripts/run-test-coverage.sh ${TEST_TARGET} ${TEST_INPUT} ${KCOV_PROGRAM} ${KCOV_ARGS} ${KCOV_REPORT_PATH})
  else()
    add_test(NAME ${TEST_TARGET} COMMAND ${CMAKE_SOURCE_DIR}/scripts/run-test.sh ${TEST_TARGET} ${TEST_INPUT})
  endif()
endfunction()

add_subdirectory(2015)

add_subdirectory(extra)
