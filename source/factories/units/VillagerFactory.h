#ifndef SOURCE_FACTORIES_UNITS_VILLAGERFACTORY_H_
#define SOURCE_FACTORIES_UNITS_VILLAGERFACTORY_H_

#include <base/UnitFactory.h>

// Creates and holds all the villagers.
class VillagerFactory : public UnitFactory {
 protected:
    // Creates a villager.
    std::shared_ptr<Unit> MakeUnit() override;

 public:
    VillagerFactory(const std::shared_ptr<ResourceManager>& resourceManager);
    ~VillagerFactory() override = default;
};

#endif  // SOURCE_FACTORIES_UNITS_VILLAGERNGFACTORY_H_
