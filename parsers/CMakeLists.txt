set(LIBRARY_NAME "parsers")

set(LIBRARY_SOURCE
    GeneralParser.h
    GeneralParser.cpp

    # Building parsers added here:
    buildings/CastleParser.h
    buildings/CastleParser.cpp

    # Unit parsers added here:
    units/VillagerParser.h
    units/VillagerParser.cpp
)

add_library(${LIBRARY_NAME} "${LIBRARY_SOURCE}")
target_link_libraries(${LIBRARY_NAME} PRIVATE string)
target_link_libraries(${LIBRARY_NAME} PRIVATE ini_parser)
target_link_libraries(${LIBRARY_NAME} PRIVATE filemanager)
