# Create a library target for raygui
add_library(raygui INTERFACE)

# Enables the implementation that raygui will use
target_compile_definitions(raygui INTERFACE RAYGUI_IMPLEMENTATION)

# Specify the include directory for raygui
target_include_directories(raygui INTERFACE "${CMAKE_CURRENT_LIST_DIR}")

# Suppress the errors and warnings coming from the library
# since there is nothing to be done about them and they are going to be annoying
# to be looked at after each build
target_compile_options(raygui INTERFACE
    -Wno-error
    -Wno-unused-result
    -Wno-stringop-overflow
)

# Raygui depends on the raylib library for some stuff
# using it in standalone mode is available but not necessary
# Standalone mode is enabled with the RAYGUI_STANDALONE option
find_package(raylib REQUIRED)
target_link_libraries(raygui INTERFACE raylib)
