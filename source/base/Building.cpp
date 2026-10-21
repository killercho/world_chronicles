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

    m_rect.x      = m_positionX;
    m_rect.y      = m_positionY;
    m_rect.width  = m_buildingTexture.width;
    m_rect.height = m_buildingTexture.height;
}

int Building::GetHealth() const noexcept {
    return m_health;
}

void Building::SetCurrentPosition(const Vector2 newPos) {
    m_positionX = newPos.x;
    m_positionY = newPos.y;

    m_rect.x = m_positionX;
    m_rect.y = m_positionY;
}

void Building::SetCurrentPosition(const unsigned int newX,
                                  const unsigned int newY) {
    m_positionX = newX;
    m_positionY = newY;

    m_rect.x = m_positionX;
    m_rect.y = m_positionY;
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
