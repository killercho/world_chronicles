#ifndef SOURCE_BASE_UNIT_H_
#define SOURCE_BASE_UNIT_H_

#include <base/PathFinder.h>
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
    // Loaded by the resource manager.
    std::shared_ptr<Texture2D> m_texture;

    // The rectangle made by the x and y and the texture size.
    Rectangle m_rect;

    // Walking box that should represent the actual wolking hitbox.
    // Used in the walking algorithm.
    Rectangle m_walkingBox;

    // Whether the current unit is selected by the mouse.
    bool m_bSelected{ false };

    // Whether the unit is currently moving.
    bool m_bMoving{ false };

    // The movement speed taken from the ini constants.
    float m_moveSpeed{ 0.0f };

    // The algorithm that is used to find a path towards a point.
    std::shared_ptr<PathFinder> m_pathFinder;

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
    // Places an outline on the walking box.
    // The template is used for easy removal of the outline with debug purposes.
    template<bool bDraw = true> void DrawWalkingBoxOutline() const {
        if constexpr (!bDraw) {
            // Do not draw if the flag is not enabled.
            return;
        }
        DrawRectangleLinesEx(m_walkingBox, 1.0f, BLUE);
    }
    // Draws the path that the figure is currently taking.
    // The template is used for easy removal of the outline with debug purposes.
    template<bool bDraw = true> void DrawCurrentPath() const {
        if constexpr (!bDraw) {
            // Do not draw if the flag is not enabled.
            return;
        }
        if (!m_bMoving) {
            // Do not try to draw when there is no path.
            return;
        }
        const auto&        path = m_pathFinder->GetWholePath();
        const unsigned int currentPointIndex =
            m_pathFinder->GetCurrentPointIndex();
        for (unsigned int i = currentPointIndex; i < path.size(); ++i) {
            DrawCircleV(path[i], 1.0f, GREEN);
        }
    }

    // Draws the unit taking into account its current state.
    virtual void Draw() = 0;

    // Move the unit towards the target point.
    // Needs to be called in the process before the draws occur.
    // Takes the move speed of the unit that is defined in the ini file.
    void Move();

    // Updates the walking hitbox depending on the new m_rect parameters.
    // Should be called whenever the rect is updated so that the walking
    // box can keep up with the updates.
    // Needs to be defined by each of the classes because the walking boxes will be different
    // for the different units.
    virtual void UpdateWalkingBox() = 0;

 public:
    Unit();
    virtual ~Unit()              = default;
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
    // Returns the walking hitbox.
    Rectangle GetWalkingBox() const noexcept;

    // Starts the movement of the unit towards the location given.
    // The actual movement is handled in the process.
    void MoveToward(const Vector2& location, const std::vector<Rectangle>& allObstacles);
    // The same target but applies additional calculations so that the final target is
    // in the middle of the unit instead of the top left corner.
    // Specifically made to adjust the mouse target movement.
    // Copies the point because it will be changed accourding to the rect of the unit.
    void MoveTowardMouse(Vector2 mousePos, const std::vector<Rectangle>& allObstacles);
};

#endif  // SOURCE_BASE_UNIT_H_
