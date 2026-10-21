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

void Castle::Draw() {
    if (!IsPlaced()) {
        DrawTexture(m_buildingTexture, m_positionX, m_positionY, GREEN);
    } else {
        DrawTexture(m_buildingTexture, m_positionX, m_positionY, WHITE);
    }
}
