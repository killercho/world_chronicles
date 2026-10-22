#include "Villager.h"
#include <raylib.h>

Villager::Villager() : m_parser(CONSTANTS_PATH "units/Villager.ini") {
    LoadTexture(ASSETS_PATH "units/villager.png",
                m_parser.GetSpriteWidth(),
                m_parser.GetSpriteHeight());
}

void Villager::Draw() {
    DrawTexture(m_texture, m_rect.x, m_rect.y, WHITE);
}

void Villager::Process(const Vector2& mousePosition) {
    const bool bMouseOver = CheckCollisionPointRec(mousePosition, m_rect);
    const bool bMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (bMouseOver && bMouseClicked) {
        SetSelected(true);
    } else if (bMouseClicked) {
        SetSelected(false);
    }

    Draw();
    if (bMouseOver) {
        DrawHoveredOutline();
    }
    DrawSelectedOutline();
}
