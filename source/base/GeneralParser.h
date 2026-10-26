#ifndef PARSERS_GENERALPARSER_H_
#define PARSERS_GENERALPARSER_H_

#include <string/String.h>
#include <ini_parser/SectionParser.h>

// Contains all the constants that the application window has.
// Parsed from the ini files.
class GeneralParser {
 private:
    unsigned int m_width{ 0 };
    unsigned int m_height{ 0 };
    unsigned int m_targetFps{ 0 };
    String       m_title;

    // Error that was found during the loading.
    String m_latestError;

    // Parses the window settings.
    void ParseWindowSettings(const SectionParser& section);

 public:
    // Parses the settings from the ini settings file
    // into the members of the class.
    // Takes the filename that leads to the ini file.
    GeneralParser(const String& filename);

    // Returns the latest error that might have happened.
    // This way no throws need to be used.
    const String& GetLatestError() const noexcept;

    // Getters for the constants:
    unsigned int  GetWidth() const noexcept;
    unsigned int  GetHeight() const noexcept;
    unsigned int  GetTargetFps() const noexcept;
    const String& GetTitle() const noexcept;
};

#endif  // PARSERS_GENERALPARSER_H_
