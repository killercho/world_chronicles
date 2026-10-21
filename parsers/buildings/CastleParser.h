#ifndef PARSERS_BUILDINGS_CASTLEPARSER_H_
#define PARSERS_BUILDINGS_CASTLEPARSER_H_

#include <string/String.h>
#include <ini_parser/SectionParser.h>

// Contains all the constants that a castle has.
// Parsed from the ini files.
class CastleParser {
 private:
    // The absolute maximum health that the castle can have.
    unsigned int m_maxHealth{ 0 };

    // The maximum size of the production queue.
    // Any production that is over that size will not be added.
    unsigned int m_productionQueueSize{ 0 };

    // Error that was found during the loading.
    String m_latestError;

    // Loads the main settings from the section given.
    void LoadMainSettings(const SectionParser& section);

 public:
    // Parses the settings from the ini settings file
    // into the members of the class.
    // Takes the filename that leads to the ini file.
    CastleParser(const String& filename);

    // Returns the latest error that might have happened.
    // This way no throws need to be used.
    const String& GetLatestError() const noexcept;

    // Getters for all the constants of the class.
    unsigned int GetMaxHealth() const noexcept;
    unsigned int GetProductionQueueSize() const noexcept;
};

#endif  // PARSERS_BUILDINGS_CASTLEPARSER_H_
