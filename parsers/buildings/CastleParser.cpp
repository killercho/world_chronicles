#include "CastleParser.h"
#include <string/String.h>
#include <ini_parser/IniParser.h>
#include <raylib.h>

CastleParser::CastleParser(const String& filename) {
    IniParser parser(filename);
    m_latestError = parser.GetLatestError();
    if (!m_latestError.Empty()) {
        TraceLog(LOG_ERROR, "Error: %s", m_latestError.c_str());
        return;
    }
    LoadMainSettings(parser.GetSection("MainSettings"));
    LoadSpriteSettings(parser.GetSection("SpriteSettings"));
}

void CastleParser::LoadSpriteSettings(const SectionParser& section) {
    if (!section.GetLatestError().Empty()) {
        return;
    }

    try {
        m_spriteWidth  = section.GetValue<unsigned int>("Width");
        m_spriteHeight = section.GetValue<unsigned int>("Height");
    } catch (const std::exception& e) {
        m_latestError = e.what();
    }
}

void CastleParser::LoadMainSettings(const SectionParser& section) {
    if (!section.GetLatestError().Empty()) {
        return;
    }

    try {
        m_maxHealth = section.GetValue<unsigned int>("Max_Health");
        m_productionQueueSize =
            section.GetValue<unsigned int>("Queue_Max_Size");
    } catch (const std::exception& e) {
        m_latestError = e.what();
    }
}

unsigned int CastleParser::GetMaxHealth() const noexcept {
    return m_maxHealth;
}

unsigned int CastleParser::GetProductionQueueSize() const noexcept {
    return m_productionQueueSize;
}

unsigned int CastleParser::GetSpriteWidth() const noexcept {
    return m_spriteWidth;
}

unsigned int CastleParser::GetSpriteHeight() const noexcept {
    return m_spriteHeight;
}

const String& CastleParser::GetLatestError() const noexcept {
    return m_latestError;
}
