#ifndef LIBS_INI_PARSER_INIPARSER_H_
#define LIBS_INI_PARSER_INIPARSER_H_

#include <string/String.h>
#include "SectionParser.h"
#include <memory>

class IniParser {
 private:
    // Holds all the sections with their names.
    // Each of the sections is parsed on its own and
    // from it the necessary information is extracted.
    std::unordered_map<String, std::shared_ptr<SectionParser>> m_allSections;

    // Error that has occured during the parsing or other use of the given files.
    // Uses this approach to avoid throwing an error in the constructors.
    // Mutable because the main variable is the only important one.
    mutable String m_fileError;

    // Checks if the file given exists as a path given.
    // Sets the error state if it does not exist.
    void CheckFileExisting(const String& filename) const;

    // Loads the information from the file given after the existing check was made.
    void LoadFromFile(const String& filename) noexcept;

 public:
    // Parses the filename given into the sections and becomes ready for use.
    explicit IniParser(const String& filename) noexcept;
    ~IniParser() = default;

    // Loads the new file that was given.
    // All the old information is cleared (including the error state).
    void LoadNewFile(const String& filename) noexcept;

    // Returns the latest error that might have occured.
    const String& GetLatestError() const noexcept;

    // Getters for the section if taking the whole section is more appropriate.
    // Throws an error if the section was not found.
    const SectionParser& GetSection(const String& section) const;
    const std::shared_ptr<SectionParser>&
    GetSectionPtr(const String& section) const;

    // Returns the value from the section that was requested.
    // Throws an error if the type is not correct for the value or the section does not exist.
    template<typename ValueType,
             std::enable_if<std::is_fundamental_v<ValueType>>>
    const ValueType GetValue(const String& section, const String& name) const {
        if (!m_allSections.contains(section)) {
            throw std::runtime_error(
                ("Section with name '" + section + "' was not found!").c_str());
        }
        return m_allSections.at(section)->GetValue<ValueType>(name);
    }
    // The same as the other GetValue function but for composite types,
    // so that they are not copied.
    template<typename ValueType,
             std::enable_if<!std::is_fundamental_v<ValueType>>>
    const ValueType& GetValue(const String& section, const String& name) const {
        if (!m_allSections.contains(section)) {
            throw std::runtime_error(
                ("Section with name '" + section + "' was not found!").c_str());
        }
        return m_allSections.at(section)->GetValue<ValueType>(name);
    }
};

#endif  // LIBS_INI_PARSER_INIPARSER_H_
