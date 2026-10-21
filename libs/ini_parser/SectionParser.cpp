#include "SectionParser.h"
#include <fstream>
#include <string>

const String& SectionParser::GetLatestError() const noexcept {
    return m_fileError;
}

void SectionParser::Clear() {
    m_allValues.clear();
    ClearError();
}

void SectionParser::ClearError() {
    m_fileError.Clear();
}

void SectionParser::LoadSection(std::ifstream& file) noexcept {
    Clear();

    std::string  lineGetter;
    unsigned int lastLinePosition = 0;
    while (std::getline(file, lineGetter)) {
        String actualLine(lineGetter);
        actualLine.Trim();
        if (actualLine.Empty()) {
            // Only spaces on the line.
            lastLinePosition = file.tellg();
            continue;
        }

        auto afterComment = actualLine.Split("#").back();
        if (afterComment.Empty()) {
            // Only a comment on the line.
            lastLinePosition = file.tellg();
            continue;
        }

        if (afterComment.Contains("[") && afterComment.Contains("]")) {
            // This section is ending.
            break;
        }

        if (!afterComment.Contains("=")) {
            m_fileError = "Row does not contain a ('key' = 'value') pair!";
            break;
        }

        auto keyValuePair = afterComment.Split("=");
        if (keyValuePair.size() != 2) {
            m_fileError =
                "Row does not contain a ('key' = 'value') pair! One of the "
                "values is missing or there are more pairs on the row!";
            break;
        }

        keyValuePair.front().Trim();
        keyValuePair.back().Trim();

        if (m_allValues.contains(keyValuePair.front())) {
            m_fileError =
                "Value '" + keyValuePair.front() +
                "' already defined in another line in the same section!";
            break;
        }

        auto value = keyValuePair.back();
        if (keyValuePair.back()[0] == '-' &&
            std::all_of(value.begin() + 1, value.end(), [](const char c) {
                return std::isdigit(c);
            })) {
            // All of the characters besides the first one are digits.
            m_allValues.insert(
                { keyValuePair.front(), value.CastFromString<int>() });
        } else if (std::all_of(value.begin(), value.end(), [](const char c) {
                       return std::isdigit(c);
                   })) {
            // All of the characters are digits.
            m_allValues.insert(
                { keyValuePair.front(), value.CastFromString<unsigned int>() });
        } else {
            if (value.Contains('"')) {
                value.Remove("\"", true);
            }
            // No idea what it is so it's a string.
            m_allValues.insert({ keyValuePair.front(), value });
        }
    }

    // When the section ends the last line needs to be returned into the file pointer.
    // Otheriwise a start of another section could be missed.
    file.seekg(lastLinePosition);
}
