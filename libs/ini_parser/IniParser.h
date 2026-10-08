#ifndef LIBS_INI_PARSER_INIPARSER_H_
#define LIBS_INI_PARSER_INIPARSER_H_

#include "SectionParser.h"

class IniParser {
 private:
    // Holds all the sections with their names.
    // Each of the sections is parsed on its own and
    // from it the necessary information is extracted.
    std::unordered_map<std::string, SectionParser> m_allSections;

 public:
    IniParser();
    ~IniParser() = default;
};

#endif  // LIBS_INI_PARSER_INIPARSER_H_
