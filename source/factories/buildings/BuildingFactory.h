#ifndef SOURCE_FACTORIES_BUILDINGS_BUILDINGFACTORY_H_
#define SOURCE_FACTORIES_BUILDINGS_BUILDINGFACTORY_H_

#include <base/Building.h>
#include <raylib.h>
#include <memory>
#include <vector>

// A base class used to create specific buildings.
// Each of the different buildings need to implement such a class so that
// they can be created.
class BuildingFactory {
 protected:
    // All the buildings that are part of the class.
    std::vector<std::shared_ptr<Building>> m_allBuildings;

 public:
    virtual ~BuildingFactory();

    // Returns the rectangles that describe the buildings
    // in this factory.
    // Used in the path algorithm to be able to avoid obstacles.
    std::vector<Rectangle> GetAllRectObstacles() const;

    // Creates a specific building.
    virtual void MakeBuilding() = 0;
};

#endif  // SOURCE_FACTORIES_BUILDINGS_BUILDINGFACTORY_H_
