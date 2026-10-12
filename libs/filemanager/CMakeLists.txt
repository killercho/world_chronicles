set(LIBRARY_NAME "filemanager")

set(LIBRARY_SOURCE
    Filemanager.h
    Filemanager.cpp
)
add_library(${LIBRARY_NAME} "${LIBRARY_SOURCE}")

target_link_libraries(${LIBRARY_NAME} PRIVATE string)

set(TEST_SOURCE
    tests/FilemanagerTests.cpp
    Filemanager.cpp
)
declare_test_with_links(filemanager_tests "${TEST_SOURCE}" filemanager_tests string)

if(ENABLE_TESTS)
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/tests/input" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()
