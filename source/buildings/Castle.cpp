#include "Castle.h"
#include <raylib.h>

Castle::Castle() : m_castleParser(CONSTANTS_PATH "buildings/Castle.ini") {
    TraceLog(LOG_TRACE,
             "Castle loaded with health: %d",
             m_castleParser.GetMaxHealth());

    LoadTexture(ASSETS_PATH "buildings/castle.png",
                m_castleParser.GetSpriteWidth(),
                m_castleParser.GetSpriteHeight());
}

void Castle::Draw(const Vector2& mousePosition) {
    if (!IsPlaced()) {
        DrawTexture(m_buildingTexture, m_rect.x, m_rect.y, GREEN);
    } else {
        DrawTexture(m_buildingTexture, m_rect.x, m_rect.y, WHITE);
    }

    DrawOutline(mousePosition);
}
