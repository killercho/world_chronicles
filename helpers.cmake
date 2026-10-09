
# Add a gtest definition that will be enabled only when the tests are enabled
function(declare_test test_name files test_folder)
    if(ENABLE_TESTS)
        add_executable(
          ${test_name}
          ${files}
        )
        target_link_libraries(
          ${test_name}
          GTest::gtest_main
        )
        include(GoogleTest)
        gtest_discover_tests(${test_name})
        # Add the test to CTest using add_test
        add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)

        message(STATUS "Test '${test_name}' added with files: (${files})")
    endif()
endfunction()

function(declare_test_with_links test_name files test_folder additional_libs)
    if(ENABLE_TESTS)
        add_executable(
          ${test_name}
          ${files}
        )
        target_link_libraries(
          ${test_name}
          ${additional_libs}
          GTest::gtest_main
        )
        include(GoogleTest)
        gtest_discover_tests(${test_name})
        # Add the test to CTest using add_test
        add_test(NAME ${test_name} COMMAND $<TARGET_FILE:${test_name}>)

        message(STATUS "Test '${test_name}' added with files: (${files})")
    endif()
endfunction()
