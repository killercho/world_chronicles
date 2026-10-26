#include "CastleFactory.h"
#include <buildings/Castle.h>

void CastleFactory::MakeBuilding() {
    m_allBuildings.emplace_back(std::make_shared<Castle>());
}
