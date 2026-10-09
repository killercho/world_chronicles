#ifndef LIBS_INI_PARSER_SECTIONPARSER_H_
#define LIBS_INI_PARSER_SECTIONPARSER_H_

#include <string/String.h>
#include <variant>
#include <unordered_map>

class SectionParser {
 private:
    // Holds all the values that the current section has.
    // All of the section is parsed in a 'key' = 'value' format.
    // Where the key is saved as the string and the variant holds the actual values.
    std::unordered_map<String, std::variant<int, unsigned int, String>>
        m_allValues;

    // Error that has occured during the parsing or other use of the given files.
    // Uses this approach to avoid throwing an error in the constructors.
    // Mutable because the main variable is the only important one.
    String m_fileError;

 public:
    SectionParser()  = default;
    ~SectionParser() = default;

    // Clears the values in the section and the error code.
    void Clear();
    // Clears the error code only.
    void ClearError();

    // Loads the section from the file given.
    // Expects the pointer to be on the first line of the section after the name.
    void LoadSection(std::ifstream& file) noexcept;

    // Returns the latest error that might have occured.
    const String& GetLatestError() const noexcept;

    // Get one of the possible values in the map but only copy if the type is fundamental.
    // Throws an error if the value name does not exist in the names or the type requested is not what
    // the variant holds.
    template<typename ValueType,
             std::enable_if<std::is_fundamental_v<ValueType>>>
    const ValueType GetValue(const String& name) const {
        if (!m_allValues.contains(name)) {
            throw std::runtime_error(
                ("Value for name '" + name + "' was not found!").c_str());
        }

        const auto& value = m_allValues.at(name);
        if (!std::holds_alternative<ValueType>(value)) {
            throw std::runtime_error(("Value for name '" + name +
                                      "' not what the type was requested!")
                                         .c_str());
        }

        return std::get<ValueType>(value);
    }
    // The same as the other GetValue function but for composite types,
    // so that they are not copied.
    template<typename ValueType,
             std::enable_if<!std::is_fundamental_v<ValueType>>>
    const ValueType& GetValue(const String& name) const {
        if (!m_allValues.contains(name)) {
            throw std::runtime_error(
                ("Value for name '" + name + "' was not found!").c_str());
        }

        const auto& value = m_allValues.at(name);
        if (!std::holds_alternative<ValueType>(value)) {
            throw std::runtime_error(("Value for name '" + name +
                                      "' not what the type was requested!")
                                         .c_str());
        }

        return std::get<ValueType>(value);
    }
};

#endif  // LIBS_INI_PARSER_SECTIONPARSER_H_
