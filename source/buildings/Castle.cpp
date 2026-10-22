#include "Castle.h"
#include <raylib.h>

Castle::Castle() : m_parser(CONSTANTS_PATH "buildings/Castle.ini") {
    LoadTexture(ASSETS_PATH "buildings/castle.png",
                m_parser.GetSpriteWidth(),
                m_parser.GetSpriteHeight());
}

void Castle::Draw() {
    if (!IsPlaced()) {
        DrawTexture(m_texture, m_rect.x, m_rect.y, GREEN);
    } else {
        DrawTexture(m_texture, m_rect.x, m_rect.y, WHITE);
    }
}

void Castle::Process(const Vector2& mousePosition) {
    const bool bMouseOver = CheckCollisionPointRec(mousePosition, m_rect);
    Draw();
    if (bMouseOver) {
        DrawHoveredOutline();
    }
    DrawSelectedOutline();
}
