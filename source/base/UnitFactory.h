#ifndef SOURCE_BASE_UNITFACTORY_H_
#define SOURCE_BASE_UNITFACTORY_H_

#include <base/Unit.h>
#include <base/ResourceManager.h>
#include <raylib.h>
#include <memory>
#include <vector>

// A base class used to create specific units.
// Each of the different units need to implement such a class so that
// they can be created.
class UnitFactory {
 private:
    // All the units that are part of the class.
    std::vector<std::shared_ptr<Unit>> m_allUnits;

 protected:
    // Resource manager from the parent class that is used for getting the textures.
    std::shared_ptr<ResourceManager> m_resourceManager;

    // Creates a specific unit.
    virtual std::shared_ptr<Unit> MakeUnit() = 0;

 public:
    UnitFactory(const std::shared_ptr<ResourceManager> resourceManager);
    virtual ~UnitFactory();

    // Creates the new unit and adds it to the rest of the units.
    void CreateNewUnit();

    // Ticks the unit factory which ticks all the units.
    // The process needs to be called when drawing so that the drawing can happen.
    void Process(const Rectangle& mouseRect, const bool bMouseReleased);
};

#endif  // SOURCE_BASE_UNITFACTORY_H_
