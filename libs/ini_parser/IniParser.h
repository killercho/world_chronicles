#ifndef LIBS_INI_PARSER_INIPARSER_H_
#define LIBS_INI_PARSER_INIPARSER_H_

#include <string/String.h>
#include "SectionParser.h"

class IniParser {
 private:
    // Holds all the sections with their names.
    // Each of the sections is parsed on its own and
    // from it the necessary information is extracted.
    std::unordered_map<String, SectionParser> m_allSections;

    // Error that has occured during the parsing or other use of the given files.
    // Mutable because the main variable is the only important one.
    mutable String m_fileError;

    // Checks if the file given exists as a path given.
    // Sets the error state if it does not exist.
    void CheckFileExisting(const String& filename) const;

    // Loads the information from the file given after the existing check was made.
    void LoadFromFile(const String& filename);

 public:
    // Parses the filename given into the sections and becomes ready for use.
    explicit IniParser(const String& filename);
    ~IniParser() = default;

    // Loads the new file that was given.
    // All the old information is cleared (including the error state).
    void LoadNewFile(const String& filename);

    // Returns the latest error that might have occured.
    const std::string& GetLatestError() const noexcept;

    // TODO: Add the rest of the methods that might be useful.
};

#endif  // LIBS_INI_PARSER_INIPARSER_H_
