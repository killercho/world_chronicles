#include "Unit.h"
#include <raylib.h>

Unit::Unit() : m_pathFinder(std::make_shared<PathFinder>()) { }

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

void Unit::MoveToward(const Vector2&                location,
                      const std::vector<Rectangle>& allObstacles) {
    m_bMoving = true;
    m_pathFinder->Request(
        Vector2(m_rect.x, m_rect.y), location, m_moveSpeed, allObstacles);
}

void Unit::MoveTowardMouse(Vector2                       mousePos,
                           const std::vector<Rectangle>& allObstacles) {
    mousePos.x -= m_rect.width / 2.0f;
    mousePos.y -= m_rect.height / 2.0f;
    MoveToward(mousePos, allObstacles);
}

void Unit::Move() {
    if (!m_bMoving) {
        // The unit is not supposed to be moving.
        return;
    }
    if (m_pathFinder->IsTargetReached()) {
        // The target was reached.
        m_bMoving = false;
        return;
    }

    const Vector2 currentPos = Vector2(m_rect.x, m_rect.y);
    float         realSpeedX = m_moveSpeed;
    float         realSpeedY = m_moveSpeed;

    // Get distance instead and if the distance is 0 move to the next point.
    // Otherwise move with a fraction of the speed required so
    // that the move target is actually possible to get to.
    if (m_pathFinder->IsPointReached(
            currentPos, m_pathFinder->GetCurrentPoint(), m_moveSpeed)) {
        m_pathFinder->MoveToNextPoint();
    }
    m_pathFinder->AdjustMoveSpeed(realSpeedX, realSpeedY, currentPos);

    const auto& nextPoint = m_pathFinder->GetCurrentPoint();

    if (nextPoint.x > m_rect.x) {
        m_rect.x += realSpeedX;
    } else if (nextPoint.x < m_rect.x) {
        m_rect.x -= realSpeedX;
    }

    if (nextPoint.y > m_rect.y) {
        m_rect.y += realSpeedY;
    } else if (nextPoint.y < m_rect.y) {
        m_rect.y -= realSpeedY;
    }
    UpdateWalkingBox();
}
