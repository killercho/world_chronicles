#include "PathFinder.h"
#include <raylib.h>
#include <stdexcept>
#include <queue>
#include <list>

void PathFinder::Reset() {
    m_pointIndex = 0;
    m_path.clear();
}

bool PathFinder::IsPointReached(const Vector2& point,
                                const Vector2& target,
                                const float    moveSpeed) const {
    return (GetManhattanDistance(point, target) < moveSpeed);
}

void PathFinder::BuildPathOrdinary(Vector2     currentPosition,
                                   const float moveSpeed,
                                   const std::vector<Rectangle>& allObstacles) {
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

void PathFinder::BuildPath(Vector2                       currentPosition,
                           const float                   moveSpeed,
                           const std::vector<Rectangle>& allObstacles) {
    // Compares the nodes by their position score.
    const auto gridLocationComparator =
        [](const std::shared_ptr<internal::GridLocation>& left,
           const std::shared_ptr<internal::GridLocation>& right) {
            return left->GetScore() < right->GetScore();
        };

    // TODO: Create a grid with a single grid square being (moveSpeed x moveSpeed) in size.
    // TODO: Calculate where the current position falls into.
    // TODO: Start the algorithm with that in mind.
    // ...
    // Make jumps in all directions and diagonals using the move speed.
    // At each jump recalculate the value of the locations around the current node
    // and add any changes.
    // If a jump has colision between the walking box and the rect in the obstacles
    // do not explore that grid location.
    // Continue until the target is reached or there are no more possible options left to explore.
    // Keep track of the seen coordinates in the grid so
    // that the seen grid spaces are not explored again.
    // ...
    // TODO: After the algorithm finishes use the middles of the grid fields that are part of the path
    // to form the positions used in the returned path.

    // Creates the priority of what is the next node that needs to be explored.
    std::priority_queue<std::shared_ptr<internal::GridLocation>,
                        std::list<std::shared_ptr<internal::GridLocation>>,
                        decltype(gridLocationComparator)>
        gridLocations(gridLocationComparator);

    // Add the starting point of the algorithm - the current position.
    /*
    gridLocations.push(std::make_shared<internal::GridLocation>(
        0,
        GetManhattanDistance(currentPosition, m_targetPoint),
        currentPosition,
        ,
        nullptr));
   */
}

void PathFinder::Request(Vector2                       currentPosition,
                         const Vector2&                target,
                         const float                   moveSpeed,
                         const std::vector<Rectangle>& allObstacles) {
    Reset();
    m_targetPoint = target;

    // BuildPathOrdinary(currentPosition, moveSpeed, allObstacles);
    BuildPath(currentPosition, moveSpeed, allObstacles);
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

unsigned int PathFinder::GetCurrentPointIndex() const noexcept {
    return m_pointIndex;
}
