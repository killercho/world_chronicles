#include "Building.h"
#include <raylib.h>

int Building::GetHealth() const noexcept {
    return m_health;
}

void Building::SetCurrentPosition(const Vector2& newPos) {
    m_rect.x = newPos.x;
    m_rect.y = newPos.y;
}

void Building::SetCurrentPosition(const unsigned int newX,
                                  const unsigned int newY) {
    m_rect.x = newX;
    m_rect.y = newY;
}

void Building::SetPositionFromMouse(const Vector2& newPos) {
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

void Building::SetSelected(const bool bSelected) {
    m_bSelected = bSelected;
}

bool Building::IsSelected() const noexcept {
    return m_bSelected;
}
