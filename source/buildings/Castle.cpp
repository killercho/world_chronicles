#include "Castle.h"
#include "raylib.h"

Castle::Castle() : m_castleParser(CONSTANTS_PATH "buildings/Castle.ini") {
    TraceLog(
        LOG_INFO, "Castle health loaded: %d", m_castleParser.GetMaxHealth());
}
