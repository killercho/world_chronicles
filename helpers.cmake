
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
    endif()
endfunction()
