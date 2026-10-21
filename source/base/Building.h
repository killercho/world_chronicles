#ifndef SOURCE_BASE_BUILDING_H_
#define SOURCE_BASE_BUILDING_H_

// Abstract base class for all of the buildings in the game
// All of the buildings in the game will inherit from this class
class Building {
 protected:
    // Health that the unit has currently
    int m_health;

    // Defense that the building has, used when other entities are attacking
    int m_defense;

 public:
    Building()                           = default;
    virtual ~Building()                  = default;
    Building(const Building&)            = default;
    Building(Building&&)                 = default;
    Building& operator=(const Building&) = default;
    Building& operator=(Building&&)      = default;

    // Plays the destroy animation and destroys the building
    // leaving a mark.
    virtual void Destroy() = 0;

    // Plays the building animation with all of
    // the building specifications like time to build.
    virtual void Build() = 0;

    // Shows the UI of the current building
    // allowing for technology research or unit creation.
    virtual void ShowUI() = 0;

    // Attacks another entity.
    virtual void Attack() = 0;

    // Covers the functionality for when the building takes damage.
    virtual void TakeDamage() = 0;
};

#endif  // SOURCE_BASE_BUILDING_H_
