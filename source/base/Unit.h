#ifndef SOURCE_BASE_UNIT_H_
#define SOURCE_BASE_UNIT_H_

#include <string/String.h>
#include <raylib.h>

// Abstract base class for all of the buildings in the game
// All of the buildings in the game will inherit from this class
class Unit {
 protected:
    // Health that the unit has currently
    int m_health{ 0 };

    // Holds the texture of the unit.
    // This would need to be replaced with something more when animations
    // and different states of the units are introduced.
    Texture2D m_texture;

    // The rectangle made by the x and y and the texture size.
    Rectangle m_rect;

    // Whether the current unit is selected by the mouse.
    bool m_bSelected{ false };

    // Whether the unit is currently moving.
    bool m_bMoving{ false };
    // The point towards which the unit should move.
    Vector2 m_targetMovePoint;

    // Loads a texture from the path of a png.
    // Uses the size given to resize the image to be the correct size.
    void LoadTexture(const String&      filename,
                     const unsigned int sizeWidth,
                     const unsigned int sizeHeight);

    // Places an outline on the unit when it is in a selected state.
    // The template is used for easy removal of the outline with debug purposes.
    template<bool bDraw = true> void DrawSelectedOutline() const {
        if constexpr (!bDraw) {
            // Do not draw if the flag is not enabled.
            return;
        }
        if (IsSelected()) {
            DrawRectangleLinesEx(m_rect, 1.0f, RED);
        }
    }

    // Draws the unit taking into account its current state.
    virtual void Draw() = 0;

    // Move the unit towards the target point.
    // Needs to be called in the process before the draws occur.
    // Takes the move speed of the unit that is defined in the ini file.
    void Move(const unsigned int moveSpeed);

 public:
    Unit() = default;
    virtual ~Unit();
    Unit(const Unit&)            = default;
    Unit(Unit&&)                 = default;
    Unit& operator=(const Unit&) = default;
    Unit& operator=(Unit&&)      = default;

    // Processes the unit for this game loop.
    // Takes the mouse position to avoid having to call the raylib getter
    // at all the units and whether the mouse click was released.
    // All of the process calls need to be done inside of the BeginDraw()-EndDraw() chain
    // because the processes are what is drawing the units.
    virtual void Process(const bool       bMouseReleased,
                         const Rectangle& mouseRect) = 0;

    // Returns the health of the unit.
    int GetHealth() const noexcept;

    // Setters for the position that the unit is on.
    void SetCurrentPosition(const Vector2& newPos);
    void SetCurrentPosition(const unsigned int newX, const unsigned int newY);

    // Set whether the unit was selected.
    void SetSelected(const bool bSelected);
    // Returns true if the unit was selected with the mouse.
    bool IsSelected() const noexcept;

    // Returns the rectangle that was calculated for the position and texture given.
    Rectangle GetRectangle() const noexcept;

    // Starts the movement of the unit towards the location given.
    // The actual movement is handled in the process.
    void MoveToward(const Vector2& location);
};

#endif  // SOURCE_BASE_UNIT_H_
