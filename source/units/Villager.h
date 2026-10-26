#ifndef SOURCE_UNITS_VILLAGER_H_
#define SOURCE_UNITS_VILLAGER_H_

#include <base/Unit.h>
#include <base/ResourceManager.h>
#include <parsers/units/VillagerParser.h>
#include <memory>

// Defines the castle building
class Villager : public Unit {
 private:
    // Holds all the constants that the villager will use during its lifetime.
    VillagerParser m_parser;

    void Draw() override;

 public:
    Villager(const std::shared_ptr<ResourceManager>& resourceManager);
    ~Villager() override = default;

    void Process(const bool       bMouseReleased,
                 const Rectangle& mouseRect) override;
};

#endif  // SOURCE_UNITS_VILLAGER_H_
