#include "CastleParser.h"
#include <string/String.h>
#include <ini_parser/IniParser.h>

CastleParser::CastleParser(const String& filename) {
    IniParser parser(filename);
    LoadMainSettings(parser.GetSection("MainSettings"));

    m_latestError = parser.GetLatestError();
}

void CastleParser::LoadMainSettings(const SectionParser& section) {
    if (!section.GetLatestError().Empty()) {
        return;
    }

    m_maxHealth           = section.GetValue<unsigned int>("Max_Health");
    m_productionQueueSize = section.GetValue<unsigned int>("Queue_Max_Size");
}

unsigned int CastleParser::GetMaxHealth() const noexcept {
    return m_maxHealth;
}

unsigned int CastleParser::GetProductionQueueSize() const noexcept {
    return m_productionQueueSize;
}

const String& CastleParser::GetLatestError() const noexcept {
    return m_latestError;
}
