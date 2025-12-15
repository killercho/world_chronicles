cmake_minimum_required(VERSION 3.31)

project(world_chronicles CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -std=c++23")

option(ENABLE_TESTS "Enable the library tests" OFF)

include(helpers.cmake)

if(ENABLE_TESTS)
    # Enable the google test library and tests when the test option was enabled
    # Include the gtest library
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
endif()

# Adding our source files
# Define PROJECT_SOURCES and HEADERS as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/source/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/source/*.h")

# Define PROJECT_INCLUDE to be the path to the include directory of the project
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/source" "${CMAKE_CURRENT_LIST_DIR}/libs")

# Declaring executable
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE "source")
target_include_directories(${PROJECT_NAME} PRIVATE "libs")

# Add and link the raylib library from the system
find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Add and link the libraries
add_subdirectory(libs)
target_link_libraries(${PROJECT_NAME} PRIVATE raygui)
target_link_libraries(${PROJECT_NAME} PRIVATE string)

# Setting release and debug constants and assets
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
    target_compile_definitions(${PROJECT_NAME} PUBLIC CONSTANTS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/constants/")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets")
    target_compile_definitions(${PROJECT_NAME} PUBLIC CONSTANTS_PATH="./constants/")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/constants/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/constants/")
else()
    message(STATUS "Nothing is enabled")
endif()
