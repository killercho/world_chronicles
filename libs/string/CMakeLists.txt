set(LIBRARY_NAME "string")

file(GLOB LIBRARY_SOURCE
    String.cpp
    String.h
)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCE})

declare_test(string_tests ${LIBRARY_SOURCE} string_tests)
