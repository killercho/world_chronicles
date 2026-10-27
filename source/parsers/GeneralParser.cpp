#include "GeneralParser.h"
#include <ini_parser/IniParser.h>
#include <ini_parser/SectionParser.h>

GeneralParser::GeneralParser(const String& filename) {
    IniParser parser(filename);
    ParseWindowSettings(parser.GetSection("WindowSettings"));

    if (m_latestError.Empty()) {
        m_latestError = parser.GetLatestError();
    }
}

void GeneralParser::ParseWindowSettings(const SectionParser& section) {
    if (!section.GetLatestError().Empty()) {
        return;
    }

    try {
        m_width     = section.GetValue<unsigned int>("Width");
        m_height    = section.GetValue<unsigned int>("Height");
        m_targetFps = section.GetValue<unsigned int>("FPS");
        m_title     = section.GetValue<String>("Title");
    } catch (const std::exception& e) {
        m_latestError = e.what();
    }
}

const String& GeneralParser::GetLatestError() const noexcept {
    return m_latestError;
}

unsigned int GeneralParser::GetWidth() const noexcept {
    return m_width;
}

unsigned int GeneralParser::GetHeight() const noexcept {
    return m_height;
}

unsigned int GeneralParser::GetTargetFps() const noexcept {
    return m_targetFps;
}

const String& GeneralParser::GetTitle() const noexcept {
    return m_title;
}
