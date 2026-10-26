#include "CastleFactory.h"
#include <buildings/Castle.h>

std::shared_ptr<Building> CastleFactory::MakeBuilding() {
    return std::make_shared<Castle>();
}
