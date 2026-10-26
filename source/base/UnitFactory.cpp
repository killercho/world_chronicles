#include "UnitFactory.h"

UnitFactory::UnitFactory(
    const std::shared_ptr<ResourceManager> resourceManager) {
    m_resourceManager = resourceManager;
}

UnitFactory::~UnitFactory() {
    m_allUnits.clear();
}

void UnitFactory::CreateNewUnit() {
    const auto newUnit = MakeUnit();
    if (newUnit == nullptr) {
        // This should not happen.
        throw std::runtime_error(
            "Could not create a new unit of the type requested!");
    }
    m_allUnits.emplace_back(newUnit);
}

void UnitFactory::Process(const Rectangle& mouseRect,
                          const bool       bMouseReleased) {
    std::for_each(
        m_allUnits.begin(),
        m_allUnits.end(),
        [&mouseRect, bMouseReleased](const std::shared_ptr<Unit>& unit) {
            unit->Process(bMouseReleased, mouseRect);
        });
}
