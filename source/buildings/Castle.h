#ifndef SOURCE_BUILDINGS_CASTLE_H_
#define SOURCE_BUILDINGS_CASTLE_H_

#include <base/Building.h>
#include <parsers/buildings/CastleParser.h>

// Defines the castle building
class Castle : public Building {
 private:
    // Holds all the constants that the castle will use during its lifetime.
    CastleParser m_castleParser;

    void Draw() override;

 public:
    Castle();
    ~Castle() override = default;

    void Process(const Vector2& mousePosition) override;
};

#endif  // SOURCE_BUILDINGS_CASTLE_H_
