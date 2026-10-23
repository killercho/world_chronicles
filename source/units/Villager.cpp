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

void Villager::Process(const bool bMouseReleased, const Rectangle& mouseRect) {
    if (bMouseReleased) {
        if (CheckCollisionRecs(m_rect, mouseRect)) {
            SetSelected(true);
        } else {
            SetSelected(false);
        }
    }

    Move();
    Draw();
    DrawSelectedOutline();
}
