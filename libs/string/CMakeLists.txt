set(LIBRARY_NAME "string")

set(LIBRARY_SOURCE
    String.cpp
    String.h
)
add_library(${LIBRARY_NAME} "${LIBRARY_SOURCE}")
target_include_directories(${LIBRARY_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

set(TEST_SOURCE
    tests/StringTests.cpp
    String.cpp
)
declare_test(string_tests "${TEST_SOURCE}" string_tests)
