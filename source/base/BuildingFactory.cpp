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

void BuildingFactory::TryPlaceBuilding(const Vector2& mousePos,
                                       const bool     bMouseClicked) {
    if (m_toPlace == nullptr) {
        // Do not try to place since there is nothing to place.
        return;
    }

    if (!m_toPlace->IsPlaced() && bMouseClicked) {
        // The building was actually placed so add it to all the buildings
        // and make sure it cannot be moved again.
        m_toPlace->SetPositionFromMouse(mousePos);
        m_toPlace->SetPlaced(true);
        m_allBuildings.emplace_back(m_toPlace);
        m_toPlace.reset();
    } else if (!m_toPlace->IsPlaced()) {
        m_toPlace->SetPositionFromMouse(mousePos);
    }
}

void BuildingFactory::CreateNewBuilding() {
    const auto newBuilding = MakeBuilding();
    if (newBuilding == nullptr) {
        // This should not happen.
        throw std::runtime_error(
            "Could not create a new building of the type requested!");
    }
    m_toPlace = newBuilding;
}

void BuildingFactory::Process(const Vector2& mousePos,
                              const bool     bMouseClicked) {
    TryPlaceBuilding(mousePos, bMouseClicked);

    std::for_each(m_allBuildings.begin(),
                  m_allBuildings.end(),
                  [&mousePos](const std::shared_ptr<Building>& building) {
                      building->Process(mousePos);
                  });
}
