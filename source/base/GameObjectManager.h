#ifndef BASE_GAMEOBJECTMANAGER_H_
#define BASE_GAMEOBJECTMANAGER_H_

#include <base/BuildingFactory.h>
#include <base/UnitFactory.h>
#include <base/ResourceManager.h>
#include <raylib.h>
#include <vector>
#include <memory>

class GameObjectManager {
 private:
    // Holds all the building factories.
    // These include a single factory for each of the building types.
    std::vector<std::shared_ptr<BuildingFactory>> m_allBuildingFactories;

    // Holds all the unit factories.
    // These include a single factory for each of the unit types.
    std::vector<std::shared_ptr<UnitFactory>> m_allUnitFactories;

    // The resource manager for all the game objects.
    std::shared_ptr<ResourceManager> m_resourceManager;

 public:
    GameObjectManager();
    ~GameObjectManager();

    // Create a new building factory and add it to the builing factories.
    // Also returns a pointer to the factory that was just created.
    // Only creates the factory type if such did not already exist,
    // in the event that such already exists returns the old factory.
    template<typename FactoryType,
             std::enable_if_t<std::is_base_of_v<BuildingFactory, FactoryType>,
                              bool> = true>
    std::shared_ptr<BuildingFactory> AddBuildingFactory() {
        for (const std::shared_ptr<BuildingFactory>& factory :
             m_allBuildingFactories) {
            const auto currentFactory =
                std::dynamic_pointer_cast<FactoryType>(factory);
            if (currentFactory != nullptr) {
                return currentFactory;
            }
        }
        m_allBuildingFactories.emplace_back(
            std::make_shared<FactoryType>(m_resourceManager));
        return m_allBuildingFactories.back();
    }
    // The same but enabled only for unit types.
    template<typename FactoryType,
             std::enable_if_t<std::is_base_of_v<UnitFactory, FactoryType>,
                              bool> = true>
    std::shared_ptr<UnitFactory> AddUnitFactory() {
        for (const std::shared_ptr<UnitFactory>& factory : m_allUnitFactories) {
            const auto currentFactory =
                std::dynamic_pointer_cast<FactoryType>(factory);
            if (currentFactory != nullptr) {
                return currentFactory;
            }
        }
        m_allUnitFactories.emplace_back(
            std::make_shared<FactoryType>(m_resourceManager));
        return m_allUnitFactories.back();
    }

    // Returns a factory that was requested.
    // Throws an error if the factory was not found.
    template<typename FactoryType,
             std::enable_if_t<std::is_base_of_v<BuildingFactory, FactoryType>,
                              bool> = true>
    std::shared_ptr<FactoryType> GetBuildingFactory() const {
        for (const std::shared_ptr<BuildingFactory>& factory :
             m_allBuildingFactories) {
            const auto currentFactory =
                std::dynamic_pointer_cast<FactoryType>(factory);
            if (currentFactory != nullptr) {
                return currentFactory;
            }
        }
        throw std::runtime_error(
            "Building factory with that type was not created!");
        return std::shared_ptr<FactoryType>();
    }
    // The same but for units.
    template<typename FactoryType,
             std::enable_if_t<std::is_base_of_v<UnitFactory, FactoryType>,
                              bool> = true>
    std::shared_ptr<FactoryType> GetUnitFactory() const {
        for (const std::shared_ptr<UnitFactory>& factory : m_allUnitFactories) {
            const auto currentFactory =
                std::dynamic_pointer_cast<FactoryType>(factory);
            if (currentFactory != nullptr) {
                return currentFactory;
            }
        }
        throw std::runtime_error(
            "Unit factory with that type was not created!");
        return std::shared_ptr<FactoryType>();
    }

    // Loops over all the building factories and collects all the obsticles.
    std::vector<Rectangle> GetAllObstacles() const;

    // Starts the unit movement for each of the unit factories added.
    void StartUnitsMovement(const Vector2& mousePos,
                            const bool     bRightMouseClicked);

    // Ticks all the buildings from the factories.
    // Called separately to avoid having to pass too many arguments.
    void ProcessBuildings(const Vector2& mousePos,
                          const bool     bLeftMouseClicked);
    // Ticks all the units from the factories.
    // Called separately to avoid having to pass too many arguments.
    void ProcessUnits(const Rectangle& mouseRect,
                      const bool       bLeftMouseReleased);
};

#endif  // BASE_GAMEOBJECTMANAGER_H_
