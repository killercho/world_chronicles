#include "CastleFactory.h"
#include <buildings/Castle.h>

CastleFactory::CastleFactory(
    const std::shared_ptr<ResourceManager>& resourceManager)
    : BuildingFactory(resourceManager) { }

std::shared_ptr<Building> CastleFactory::MakeBuilding() {
    return std::make_shared<Castle>(m_resourceManager);
}
