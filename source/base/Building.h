#ifndef SOURCE_BASE_BUILDING_H_
#define SOURCE_BASE_BUILDING_H_

#include <string/String.h>
#include <raylib.h>

// Abstract base class for all of the buildings in the game
// All of the buildings in the game will inherit from this class
class Building {
 protected:
    // Health that the unit has currently
    int m_health{ 0 };

    // The coordinates of the building on the window.
    unsigned int m_positionX{ 0 };
    unsigned int m_positionY{ 0 };

    // Holds the texture of the building.
    // This would need to be replaced with something more when animations
    // and different states of the building are introduced.
    Texture2D m_buildingTexture;

    // Whether the building was placed or not.
    bool m_bPlaced{ false };

    // Loads a texture from the path of a png.
    // Uses the size given to resize the image to be the correct size.
    void LoadTexture(const String&      filename,
                     const unsigned int sizeWidth,
                     const unsigned int sizeHeight);

 public:
    Building() = default;
    virtual ~Building();
    Building(const Building&)            = default;
    Building(Building&&)                 = default;
    Building& operator=(const Building&) = default;
    Building& operator=(Building&&)      = default;

    // Draws the building taking into account its current state.
    virtual void Draw() = 0;

    // Returns the health of the building.
    int GetHealth() const noexcept;

    // Setters for the position that the building is on.
    void SetCurrentPosition(const Vector2 newPos);
    void SetCurrentPosition(const unsigned int newX, const unsigned int newY);

    // Set whether the building was placed.
    void SetPlaced(const bool bPlaced);
};

#endif  // SOURCE_BASE_BUILDING_H_
