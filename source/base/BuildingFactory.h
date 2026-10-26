#ifndef SOURCE_BASE_BUILDINGFACTORY_H_
#define SOURCE_BASE_BUILDINGFACTORY_H_

#include <base/Building.h>
#include <raylib.h>
#include <memory>
#include <vector>

// A base class used to create specific buildings.
// Each of the different buildings need to implement such a class so that
// they can be created.
class BuildingFactory {
 private:
    // This is the building that needs to follow the cursor and be able to be placed.
    // Set when a new building is created.
    std::shared_ptr<Building> m_toPlace;

    // All the buildings that are part of the class.
    std::vector<std::shared_ptr<Building>> m_allBuildings;

    // Trying to place a building somewhere on the map.
    // While the building is not placed it should follow the cursor and it should have a green hue.
    // The try place is called at each process call but is actually executed only
    // when the m_toPlace member is not nullptr.
    void TryPlaceBuilding(const Vector2& mousePos, const bool bMouseClicked);

 protected:
    // Creates a specific building that will be tried to be placed.
    virtual std::shared_ptr<Building> MakeBuilding() = 0;

 public:
    virtual ~BuildingFactory();

    // Returns the rectangles that describe the buildings
    // in this factory.
    // Used in the path algorithm to be able to avoid obstacles.
    std::vector<Rectangle> GetAllRectObstacles() const;

    // Simulates making the building and trying to place it.
    // If the creation and placement were successful
    // adds the new building to the created buildings.
    void CreateNewBuilding();

    // Ticks the building factory which ticks all the buildings.
    void Process(const Vector2& mousePos, const bool bMouseClicked);
};

#endif  // SOURCE_BASE_BUILDINGFACTORY_H_
