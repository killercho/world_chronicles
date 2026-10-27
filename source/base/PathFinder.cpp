#include "PathFinder.h"
#include <raylib.h>
#include <stdexcept>

void PathFinder::Reset() {
    m_pointIndex = 0;
    m_path.clear();
}

bool PathFinder::IsPointReached(const Vector2& point,
                                const Vector2& target,
                                const float    moveSpeed) const {
    TraceLog(LOG_INFO,
             "distance manhattan: %f, x distance old: %f, y distance old: %f",
             GetManhattanDistance(point, target),
             std::abs(target.x - point.x),
             std::abs(target.y - point.y));
    return (GetManhattanDistance(point, target) < moveSpeed);
}

void PathFinder::Request(Vector2        currentPosition,
                         const Vector2& target,
                         const float    moveSpeed) {
    Reset();
    m_targetPoint = target;

    while (!IsPointReached(currentPosition, m_targetPoint, moveSpeed)) {
        if (m_targetPoint.x > currentPosition.x) {
            currentPosition.x += moveSpeed;
        } else if (m_targetPoint.x < currentPosition.x) {
            currentPosition.x -= moveSpeed;
        }

        if (m_targetPoint.y > currentPosition.y) {
            currentPosition.y += moveSpeed;
        } else if (m_targetPoint.y < currentPosition.y) {
            currentPosition.y -= moveSpeed;
        }
        m_path.emplace_back(currentPosition);
    }
}

const Vector2& PathFinder::GetCurrentPoint() const {
    if (m_path.empty()) {
        throw std::runtime_error(
            "Path needs to be requested before the points can be taken!");
    }

    if (m_pointIndex > m_path.size() - 1) {
        return m_path.back();
    }
    return m_path[m_pointIndex];
}

void PathFinder::MoveToNextPoint() {
    m_pointIndex++;
}

const std::vector<Vector2>& PathFinder::GetWholePath() const noexcept {
    return m_path;
}

bool PathFinder::IsTargetReached() const noexcept {
    return m_pointIndex == m_path.size() - 1;
}

float PathFinder::GetManhattanDistance(const Vector2& first,
                                       const Vector2& second) {
    return std::abs(first.x - second.x) + std::abs(first.y - second.y);
}

void PathFinder::AdjustMoveSpeed(float&         moveSpeedX,
                                 float&         moveSpeedY,
                                 const Vector2& currentPosition) const {
    const auto& targetPoint = GetCurrentPoint();
    const float distanceX   = std::abs(currentPosition.x - targetPoint.x);
    const float distanceY   = std::abs(currentPosition.y - targetPoint.y);
    if (moveSpeedX > distanceX) {
        moveSpeedX = distanceX;
    }
    if (moveSpeedY > distanceY) {
        moveSpeedY = distanceY;
    }
}
