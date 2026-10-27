#include "VillagerParser.h"
#include <string/String.h>
#include <ini_parser/IniParser.h>
#include <raylib.h>

VillagerParser::VillagerParser(const String& filename) {
    IniParser parser(filename);
    m_latestError = parser.GetLatestError();
    if (!m_latestError.Empty()) {
        TraceLog(LOG_ERROR, "Error: %s", m_latestError.c_str());
        return;
    }
    LoadMainSettings(parser.GetSection("MainSettings"));
    LoadSpriteSettings(parser.GetSection("SpriteSettings"));
    LoadWalkingBoxSettings(parser.GetSection("WalkingBoxSettings"));
}

void VillagerParser::LoadWalkingBoxSettings(const SectionParser& section) {
    if (!section.GetLatestError().Empty()) {
        return;
    }

    try {
        m_walkingBoxWidth  = section.GetValue<unsigned int>("Width");
        m_walkingBoxHeight = section.GetValue<unsigned int>("Height");
    } catch (const std::exception& e) {
        m_latestError = e.what();
    }
}

void VillagerParser::LoadSpriteSettings(const SectionParser& section) {
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

void VillagerParser::LoadMainSettings(const SectionParser& section) {
    if (!section.GetLatestError().Empty()) {
        return;
    }

    try {
        m_maxHealth      = section.GetValue<unsigned int>("Max_Health");
        m_moveSpeed      = section.GetValue<unsigned int>("Move_Speed");
        m_moveSpeedScale = section.GetValue<unsigned int>("Move_Speed_Scale");
    } catch (const std::exception& e) {
        m_latestError = e.what();
    }
}

unsigned int VillagerParser::GetMaxHealth() const noexcept {
    return m_maxHealth;
}

unsigned int VillagerParser::GetMoveSpeed() const noexcept {
    return m_moveSpeed;
}

unsigned int VillagerParser::GetMoveSpeedScale() const noexcept {
    return m_moveSpeedScale;
}

unsigned int VillagerParser::GetSpriteWidth() const noexcept {
    return m_spriteWidth;
}

unsigned int VillagerParser::GetSpriteHeight() const noexcept {
    return m_spriteHeight;
}

unsigned int VillagerParser::GetWalkingBoxWidth() const noexcept {
    return m_walkingBoxWidth;
}

unsigned int VillagerParser::GetWalkingBoxHeight() const noexcept {
    return m_walkingBoxHeight;
}

const String& VillagerParser::GetLatestError() const noexcept {
    return m_latestError;
}
