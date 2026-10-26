#include "BuildingFactory.h"

BuildingFactory::~BuildingFactory() {
    m_allBuildings.clear();
}

std::vector<Rectangle> BuildingFactory::GetAllRectObstacles() const {
    std::vector<Rectangle> allRects;
    for (const auto& building : m_allBuildings) {
        allRects.emplace_back(building->GetRectangle());
    }
    return allRects;
}
