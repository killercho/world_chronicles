#ifndef LIBS_INI_PARSER_SECTIONPARSER_H_
#define LIBS_INI_PARSER_SECTIONPARSER_H_

#include <String.h>
#include <string>
#include <variant>
#include <unordered_map>

class SectionParser {
 private:
    // Holds all the values that the current section has.
    // All of the section is parsed in a 'key' = 'value' format.
    // Where the key is saved as the string and the variant holds the actual values.
    std::unordered_map<String, std::variant<int, unsigned int, std::string>>
        m_allValues;

 public:
    SectionParser();
    ~SectionParser() = default;
};

#endif  // LIBS_INI_PARSER_SECTIONPARSER_H_
