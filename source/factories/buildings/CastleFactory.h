#ifndef SOURCE_FACTORIES_BUILDINGS_CASTLEFACTORY_H_
#define SOURCE_FACTORIES_BUILDINGS_CASTLEFACTORY_H_

#include <base/BuildingFactory.h>

// Creates and holds all the castle buildings.
class CastleFactory : public BuildingFactory {
 protected:
    // Creates a castle building.
    std::shared_ptr<Building> MakeBuilding() override;

 public:
    CastleFactory(const std::shared_ptr<ResourceManager>& resourceManager);
    ~CastleFactory() override = default;
};

#endif  // SOURCE_FACTORIES_BUILDINGS_BUILDINGFACTORY_H_
