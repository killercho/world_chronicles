#ifndef PARSERS_UNITS_VILLAGERPARSER_H_
#define PARSERS_UNITS_VILLAGERPARSER_H_

#include <string/String.h>
#include <ini_parser/SectionParser.h>

// Contains all the constants that a villager has.
// Parsed from the ini files.
class VillagerParser {
 private:
    // The absolute maximum health that the castle can have.
    unsigned int m_maxHealth{ 0 };

    // Sprite sizes that will be visualized.
    unsigned int m_spriteWidth;
    unsigned int m_spriteHeight;

    // The move speed of the unit.
    // The speed is converted to an appropriate float before being used.
    // Taken as an int to avoid any issues with floating points.
    unsigned int m_moveSpeed;

    // Error that was found during the loading.
    String m_latestError;

    // Loads the main settings from the section given.
    void LoadMainSettings(const SectionParser& section);
    void LoadSpriteSettings(const SectionParser& section);

 public:
    // Parses the settings from the ini settings file
    // into the members of the class.
    // Takes the filename that leads to the ini file.
    VillagerParser(const String& filename);

    // Returns the latest error that might have happened.
    // This way no throws need to be used.
    const String& GetLatestError() const noexcept;

    // Getters for all the constants of the class.
    unsigned int GetMaxHealth() const noexcept;
    unsigned int GetMoveSpeed() const noexcept;
    unsigned int GetSpriteWidth() const noexcept;
    unsigned int GetSpriteHeight() const noexcept;
};

#endif  // PARSERS_UNITS_VILLAGERPARSER_H_
