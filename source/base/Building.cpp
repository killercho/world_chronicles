#include "Building.h"
#include <raylib.h>

Building::~Building() {
    UnloadTexture(m_buildingTexture);
}

void Building::LoadTexture(const String&      filename,
                           const unsigned int sizeWidth,
                           const unsigned int sizeHeight) {
    Image newImage = LoadImage(filename.c_str());
    ImageResizeNN(&newImage, sizeWidth, sizeHeight);

    m_buildingTexture = LoadTextureFromImage(newImage);

    UnloadImage(newImage);

    m_rect.x      = 0;
    m_rect.y      = 0;
    m_rect.width  = m_buildingTexture.width;
    m_rect.height = m_buildingTexture.height;
}

int Building::GetHealth() const noexcept {
    return m_health;
}

void Building::SetCurrentPosition(const Vector2 newPos) {
    m_rect.x = newPos.x;
    m_rect.y = newPos.y;
}

void Building::SetCurrentPosition(const unsigned int newX,
                                  const unsigned int newY) {
    m_rect.x = newX;
    m_rect.y = newY;
}

void Building::SetPositionFromMouse(const Vector2 newPos) {
    m_rect.x = newPos.x - m_rect.width / 2.0f;
    m_rect.y = newPos.y - m_rect.height / 2.0f;
}

void Building::SetPlaced(const bool bPlaced) {
    m_bPlaced = true;
}

bool Building::IsPlaced() const noexcept {
    return m_bPlaced;
}

Rectangle Building::GetRectangle() const noexcept {
    return m_rect;
}
