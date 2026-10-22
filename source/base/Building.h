#ifndef SOURCE_BASE_BUILDING_H_
#define SOURCE_BASE_BUILDING_H_

#include <string/String.h>
#include <raylib.h>

// Abstract base class for all of the buildings in the game
// All of the buildings in the game will inherit from this class
class Building {
 protected:
    // Health that the building has currently.
    int m_health{ 0 };

    // Holds the texture of the building.
    // This would need to be replaced with something more when animations
    // and different states of the building are introduced.
    Texture2D m_texture;

    // The rectangle made by the x and y and the texture size.
    Rectangle m_rect;

    // Whether the building was placed or not.
    bool m_bPlaced{ false };

    // Whether the current building is selected by the mouse.
    bool m_bSelected{ false };

    // Loads a texture from the path of a png.
    // Uses the size given to resize the image to be the correct size.
    void LoadTexture(const String&      filename,
                     const unsigned int sizeWidth,
                     const unsigned int sizeHeight);

    // Places an outline on the building when the mouse position is over the texture.
    // The template is used for easy removal of the outline with debug purposes.
    template<bool bDraw = true> void DrawHoveredOutline() const {
        if constexpr (!bDraw) {
            // Do not draw if the flag is not enabled.
            return;
        }
        if (IsPlaced()) {
            DrawRectangleLinesEx(m_rect, 1.0f, GREEN);
        }
    }

    // Places an outline on the building when it is in a selected state.
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

    // Draws the building taking into account its current state.
    virtual void Draw() = 0;

 public:
    Building() = default;
    virtual ~Building();
    Building(const Building&)            = default;
    Building(Building&&)                 = default;
    Building& operator=(const Building&) = default;
    Building& operator=(Building&&)      = default;

    // Processes the building for this game loop.
    // Takes the mouse position to avoid having to call the raylib getter
    // at all the buildings.
    // All of the process calls need to be done inside of the BeginDraw()-EndDraw() chain
    // because the processes are what is drawing the buildings.
    virtual void Process(const Vector2& mousePosition) = 0;

    // Returns the health of the building.
    int GetHealth() const noexcept;

    // Setters for the position that the building is on.
    void SetCurrentPosition(const Vector2& newPos);
    void SetCurrentPosition(const unsigned int newX, const unsigned int newY);
    // Sets the current position from the mouse position.
    // Includes an offset from the mouse pointer to the middle of the texture.
    void SetPositionFromMouse(const Vector2& newPos);

    // Set whether the building was placed.
    void SetPlaced(const bool bPlaced);
    // Returns true if the building was placed.
    bool IsPlaced() const noexcept;

    // Set whether the building was selected.
    void SetSelected(const bool bSelected);
    // Returns true if the building was selected with the mouse.
    bool IsSelected() const noexcept;

    // Returns the rectangle that was calculated for the position and texture given.
    Rectangle GetRectangle() const noexcept;
};

#endif  // SOURCE_BASE_BUILDING_H_
