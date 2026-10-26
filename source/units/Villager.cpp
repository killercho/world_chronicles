#include "Villager.h"
#include <raylib.h>

Villager::Villager(const std::shared_ptr<ResourceManager>& resourceManager)
    : m_parser(CONSTANTS_PATH "units/Villager.ini") {
    m_texture    = resourceManager->GetTexture(ASSETS_PATH "units/villager.png",
                                            m_parser.GetSpriteWidth(),
                                            m_parser.GetSpriteHeight());
    m_rect.x     = 0;
    m_rect.y     = 0;
    m_rect.width = m_texture->width;
    m_rect.height = m_texture->height;
}

void Villager::Draw() {
    DrawTexture(*m_texture, m_rect.x, m_rect.y, WHITE);
}

void Villager::Process(const bool bMouseReleased, const Rectangle& mouseRect) {
    if (bMouseReleased) {
        if (CheckCollisionRecs(m_rect, mouseRect)) {
            SetSelected(true);
        } else {
            SetSelected(false);
        }
    }

    Move(m_parser.GetMoveSpeed());
    Draw();
    DrawSelectedOutline();
}
