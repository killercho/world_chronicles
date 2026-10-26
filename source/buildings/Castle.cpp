#include "Castle.h"
#include <raylib.h>

Castle::Castle(const std::shared_ptr<ResourceManager>& resourceManager)
    : m_parser(CONSTANTS_PATH "buildings/Castle.ini") {
    m_texture = resourceManager->GetTexture(ASSETS_PATH "buildings/castle.png",
                                            m_parser.GetSpriteWidth(),
                                            m_parser.GetSpriteHeight());
    m_rect.x  = 0;
    m_rect.y  = 0;
    m_rect.width  = m_texture->width;
    m_rect.height = m_texture->height;
}

void Castle::Draw() {
    if (!IsPlaced()) {
        DrawTexture(*m_texture, m_rect.x, m_rect.y, GREEN);
    } else {
        DrawTexture(*m_texture, m_rect.x, m_rect.y, WHITE);
    }
}

void Castle::Process(const Vector2& mousePosition) {
    const bool bMouseOver    = CheckCollisionPointRec(mousePosition, m_rect);
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
