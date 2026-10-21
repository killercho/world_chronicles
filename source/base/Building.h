#ifndef SOURCE_BASE_BUILDING_H_
#define SOURCE_BASE_BUILDING_H_

// Abstract base class for all of the buildings in the game
// All of the buildings in the game will inherit from this class
class Building {
 protected:
    // Health that the unit has currently
    int m_health{ 0 };

 public:
    Building()                           = default;
    virtual ~Building()                  = default;
    Building(const Building&)            = default;
    Building(Building&&)                 = default;
    Building& operator=(const Building&) = default;
    Building& operator=(Building&&)      = default;

    // Returns the health of the building.
    int GetHealth() const noexcept { return m_health; }
};

#endif  // SOURCE_BASE_BUILDING_H_
