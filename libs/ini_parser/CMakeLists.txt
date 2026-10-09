
set(LIBRARY_NAME "ini_parser")

set(LIBRARY_SOURCE
    IniParser.cpp
    IniParser.h
    SectionParser.cpp
    SectionParser.h
)
add_library(${LIBRARY_NAME} "${LIBRARY_SOURCE}")

target_link_libraries(${LIBRARY_NAME} PRIVATE string)

set(TEST_SOURCE
    tests/IniParserTests.cpp
    IniParser.cpp
    SectionParser.cpp
)
declare_test(ini_parser_tests "${TEST_SOURCE}" ini_parser_tests)
