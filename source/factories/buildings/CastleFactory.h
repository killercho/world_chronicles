#ifndef SOURCE_FACTORIES_BUILDINGS_CASTLEFACTORY_H_
#define SOURCE_FACTORIES_BUILDINGS_CASTLEFACTORY_H_

#include <base/BuildingFactory.h>

// Creates and holds all the castle buildings.
class CastleFactory : public BuildingFactory {
 public:
    ~CastleFactory() override = default;

    // Creates a castle buidling
    void MakeBuilding() override;
};

#endif  // SOURCE_FACTORIES_BUILDINGS_BUILDINGFACTORY_H_
