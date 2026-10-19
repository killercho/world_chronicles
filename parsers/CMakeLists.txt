set(LIBRARY_NAME "parsers")

set(LIBRARY_SOURCE
    # Building parsers added here:
    buildings/CastleParser.h
    buildings/CastleParser.cpp

    # Unit parsers added here:
)

add_library(${LIBRARY_NAME} "${LIBRARY_SOURCE}")
