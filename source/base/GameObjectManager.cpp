#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
    : m_resourceManager(std::make_shared<ResourceManager>()) { }

GameObjectManager::~GameObjectManager() {
    m_allBuildingFactories.clear();
    m_allUnitFactories.clear();
}

std::vector<Rectangle> GameObjectManager::GetAllObstacles() const {
    std::vector<Rectangle> result;
    std::for_each(m_allBuildingFactories.begin(),
                  m_allBuildingFactories.end(),
                  [&result](const std::shared_ptr<BuildingFactory>& factory) {
                      const auto obstacles = factory->GetAllRectObstacles();
                      result.insert(
                          result.end(), obstacles.begin(), obstacles.begin());
                  });
    return result;
}

void GameObjectManager::StartUnitsMovement(const Vector2& mousePos,
                                           const bool     bRightMouseClicked) {
    if (bRightMouseClicked) {
        std::for_each(m_allUnitFactories.begin(),
                      m_allUnitFactories.end(),
                      [&mousePos, bRightMouseClicked](
                          const std::shared_ptr<UnitFactory>& factory) {
                          factory->StartMove(mousePos, bRightMouseClicked);
                      });
    }
}

void GameObjectManager::ProcessBuildings(const Vector2& mousePos,
                                         const bool     bLeftMouseClicked) {
    std::for_each(m_allBuildingFactories.begin(),
                  m_allBuildingFactories.end(),
                  [&mousePos, bLeftMouseClicked](
                      const std::shared_ptr<BuildingFactory>& factory) {
                      factory->Process(mousePos, bLeftMouseClicked);
                  });
}

void GameObjectManager::ProcessUnits(const Rectangle& mouseRect,
                                     const bool       bLeftMouseReleased) {
    std::for_each(m_allUnitFactories.begin(),
                  m_allUnitFactories.end(),
                  [&mouseRect, bLeftMouseReleased](
                      const std::shared_ptr<UnitFactory>& factory) {
                      factory->Process(mouseRect, bLeftMouseReleased);
                  });
}
