#ifndef BASE_PATHFINDER_H_
#define BASE_PATHFINDER_H_

#include <raylib.h>
#include <vector>
#include <memory>

namespace internal {
// Holds a single location on the grid that is used in the pathfinding algorithm.
struct GridLocation {
    // Distance from the grid location to the start of the algorithm.
    // Updated after each step in any direction using the parent.
    float distanceToStart{ 0.0f };
    // Distance from the grid location to the target of the algorithm.
    // Calculated using the manhattan distance function from the path class.
    float distanceToTarget{ 0.0f };

    // The actual location of the grid on the map.
    Vector2 coordinates;

    // The parent that led to the current location.
    std::shared_ptr<GridLocation> parent;

    // Returns the current grid location score.
    float GetScore() const noexcept {
        return distanceToStart + distanceToTarget;
    }

    GridLocation() = default;
    GridLocation(const float                          newDistanceToStart,
                 const float                          newDistanceToTarget,
                 const Vector2&                       newCoordinates,
                 const std::shared_ptr<GridLocation>& newParent)
        : distanceToStart(newDistanceToStart),
          distanceToTarget(newDistanceToTarget), coordinates(newCoordinates),
          parent(newParent) { }
};
}  // namespace internal

// Contains the logic used for a unit to find a path.
// Each unit has a single one and the path created is individual.
class PathFinder {
 private:
    // The target point of the current path.
    Vector2 m_targetPoint;

    // The index of the current point that needs to be given to the unit.
    // Changed after each take.
    unsigned int m_pointIndex;
    // The points that will be used to get to the target.
    std::vector<Vector2> m_path;

    // Executes the pathfinding algorithm (A*) and builds the path that will be used.
    void BuildPath(Vector2                       currentPosition,
                   const float                   moveSpeed,
                   const std::vector<Rectangle>& allObstacles);
    // Executes the ordinary and normie way to build a path.
    void BuildPathOrdinary(Vector2                       currentPosition,
                           const float                   moveSpeed,
                           const std::vector<Rectangle>& allObstacles);

    // Returns the manhattan distance between two points.
    static float GetManhattanDistance(const Vector2& first,
                                      const Vector2& second);

 public:
    // Resets the state of the path to the initial.
    void Reset();

    // Requests a path to a target point and prepares
    // the points that the unit needs to move towards.
    // Takes the move speed to correctly calculate the grid so that the target is reachable
    // and it's as close to the perceived speed.
    void Request(Vector2                       currentPosition,
                 const Vector2&                target,
                 const float                   moveSpeed,
                 const std::vector<Rectangle>& allObstacles);

    // Returns the current point that a unit needs to move towards.
    // If there are no more points always returns the last point in the path.
    // Throws an error if a point is trying to be taken but the path was not created.
    const Vector2& GetCurrentPoint() const;

    // Moves the index to the next point that needs to be moved towards.
    void MoveToNextPoint();

    // Returns the entire calculated path to the target.
    const std::vector<Vector2>& GetWholePath() const noexcept;

    // Returnes the index of the current point on the path that was chosen.
    unsigned int GetCurrentPointIndex() const noexcept;

    // Returns whether the target was reached.
    // This is when the unit needs to stop requesting a new path.
    // This is only true when there are no more points to be taken.
    bool IsTargetReached() const noexcept;

    // Returns true if the point given is considered an end to the path,
    // and actually the target.
    // Used during the computation process.
    bool IsPointReached(const Vector2& point,
                        const Vector2& target,
                        const float    moveSpeed) const;

    // Adjust the move speed to be able to reach the target.
    // Only changes the speed down to something that will match the distance to the target
    // if the distance is less than the move speed itself.
    void AdjustMoveSpeed(float&         moveSpeedX,
                         float&         moveSpeedY,
                         const Vector2& currentPosition) const;
};

#endif  // BASE_PATHFINDER_H_
