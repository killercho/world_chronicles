#include "Unit.h"
#include <raylib.h>

Unit::~Unit() {
    UnloadTexture(m_texture);
}

void Unit::LoadTexture(const String&      filename,
                       const unsigned int sizeWidth,
                       const unsigned int sizeHeight) {
    Image newImage = LoadImage(filename.c_str());
    ImageResizeNN(&newImage, sizeWidth, sizeHeight);

    m_texture = LoadTextureFromImage(newImage);

    UnloadImage(newImage);

    m_rect.x      = 0;
    m_rect.y      = 0;
    m_rect.width  = m_texture.width;
    m_rect.height = m_texture.height;
}

int Unit::GetHealth() const noexcept {
    return m_health;
}

void Unit::SetCurrentPosition(const Vector2& newPos) {
    m_rect.x = newPos.x;
    m_rect.y = newPos.y;
}

void Unit::SetCurrentPosition(const unsigned int newX,
                              const unsigned int newY) {
    m_rect.x = newX;
    m_rect.y = newY;
}

Rectangle Unit::GetRectangle() const noexcept {
    return m_rect;
}

void Unit::SetSelected(const bool bSelected) {
    m_bSelected = bSelected;
}

bool Unit::IsSelected() const noexcept {
    return m_bSelected;
}
