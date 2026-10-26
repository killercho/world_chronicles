#include "VillagerFactory.h"
#include <units/Villager.h>

VillagerFactory::VillagerFactory(
    const std::shared_ptr<ResourceManager>& resourceManager)
    : UnitFactory(resourceManager) { }

std::shared_ptr<Unit> VillagerFactory::MakeUnit() {
    return std::make_shared<Villager>(m_resourceManager);
}
