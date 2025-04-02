#ifndef SOURCE_BASE_BUILDING_H_
#define SOURCE_BASE_BUILDING_H_

// Abstract base class for all of the buildings in the game
// All of the buildings in the game will inherit from this class

class Building {
 private:
    // TODO: Add the rest of the fields that the base class should have
    int m_health;

 public:
    Building(const Building&)            = default;
    Building(Building&&)                 = default;
    Building& operator=(const Building&) = default;
    Building& operator=(Building&&)      = default;

    // TODO: Add all of the base functions that the base class should have like:
    //  Destroy() - that plays the destroy animation
    //  Build() - that plays the destroy animation
    //  ShowUI() - that plays the destroy animation
    //  ...
};

#endif  // SOURCE_BASE_BUILDING_H_
