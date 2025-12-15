#ifndef LIBS_INI_PARSER_INIPARSER_H_
#define LIBS_INI_PARSER_INIPARSER_H_

#include <unordered_map>
#include <string>
#include <vector>

class IniParser {
 private:
    // Holds the section names mapped to the lines of the section.
    // This way the data of the section can be taken later whenever asked for.
    std::unordered_map<std::string, std::vector<std::string>> m_sections;

 public:
    IniParser();
    ~IniParser() = default;
};

#endif  // LIBS_INI_PARSER_INIPARSER_H_
