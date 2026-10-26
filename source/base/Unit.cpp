#include "Unit.h"
#include <raylib.h>

int Unit::GetHealth() const noexcept {
    return m_health;
}

void Unit::SetCurrentPosition(const Vector2& newPos) {
    m_rect.x = newPos.x;
    m_rect.y = newPos.y;
    UpdateWalkingBox();
}

void Unit::SetCurrentPosition(const unsigned int newX,
                              const unsigned int newY) {
    m_rect.x = newX;
    m_rect.y = newY;
    UpdateWalkingBox();
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

void Unit::MoveToward(const Vector2& location) {
    m_bMoving         = true;
    m_targetMovePoint = location;
}

void Unit::MoveTowardMouse(Vector2 mousePos) {
    mousePos.x -= m_rect.width / 2.0f;
    mousePos.y -= m_rect.height / 2.0f;
    MoveToward(mousePos);
}

void Unit::Move(const unsigned int moveSpeed) {
    if (!m_bMoving) {
        // The unit is not supposed to be moving.
        return;
    }
    if (std::abs(m_targetMovePoint.x - m_rect.x) < 0.1 &&
        std::abs(m_targetMovePoint.y - m_rect.y) < 0.1) {
        // The end condition for the movement to stop.
        m_bMoving = false;
        return;
    }

    const float realSpeed = moveSpeed / 10.0f;

    if (m_targetMovePoint.x > m_rect.x) {
        m_rect.x += realSpeed;
    } else if (m_targetMovePoint.x < m_rect.x) {
        m_rect.x -= realSpeed;
    }

    if (m_targetMovePoint.y > m_rect.y) {
        m_rect.y += realSpeed;
    } else if (m_targetMovePoint.y < m_rect.y) {
        m_rect.y -= realSpeed;
    }
    UpdateWalkingBox();
}
