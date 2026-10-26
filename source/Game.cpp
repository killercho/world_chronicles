#include "Game.h"
#include <raygui.h>
#include <raylib.h>

Game::Game() : m_generalParser(CONSTANTS_PATH "GeneralSettings.ini") { }
Game::~Game() {
    CloseWindow();
}

void Game::InitializeWindow() {
    if (!m_generalParser.GetLatestError().Empty()) {
        throw std::runtime_error("Error when parsing the window settings: " +
                                 m_generalParser.GetLatestError().GetData());
    }
    InitWindow(m_generalParser.GetWidth(),
               m_generalParser.GetHeight(),
               m_generalParser.GetTitle().c_str());
    SetTargetFPS(m_generalParser.GetTargetFps());
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    m_gameObjectManager->AddBuildingFactory<CastleFactory>();
    m_gameObjectManager->AddUnitFactory<VillagerFactory>();
}

bool Game::ShouldExit() const {
    return WindowShouldClose();
}

void Game::Process() {
    const Vector2 mousePos           = GetMousePosition();
    const bool    bLeftMouseClicked  = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    const bool    bRightMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    const bool    bLeftMouseReleased = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    DrawMouseRectangle();

    if (IsKeyPressed(KEY_C)) {
        const auto factory =
            m_gameObjectManager->GetBuildingFactory<CastleFactory>();
        factory->CreateNewBuilding();
    }
    if (IsKeyPressed(KEY_V)) {
        const auto factory =
            m_gameObjectManager->GetUnitFactory<VillagerFactory>();
        factory->CreateNewUnit();
    }

    m_gameObjectManager->StartUnitsMovement(mousePos, bRightMouseClicked);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_gameObjectManager->ProcessBuildings(mousePos, bLeftMouseClicked);
    m_gameObjectManager->ProcessUnits(m_mouseRect, bLeftMouseReleased);

    EndDrawing();
}

void Game::DrawMouseRectangle() {
    const Vector2 mousePos      = GetMousePosition();
    const bool    bMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (bMouseClicked) {
        m_mouseRect.x      = mousePos.x;
        m_mouseRect.y      = mousePos.y;
        m_mouseRect.height = 1;
        m_mouseRect.width  = 1;
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (m_mouseRect.x >= mousePos.x) {
            m_mouseRect.width += m_mouseRect.x - mousePos.x;
            m_mouseRect.x      = mousePos.x;
        } else {
            m_mouseRect.width = mousePos.x - m_mouseRect.x;
        }
        if (m_mouseRect.y >= mousePos.y) {
            m_mouseRect.height += m_mouseRect.y - mousePos.y;
            m_mouseRect.y       = mousePos.y;
        } else {
            m_mouseRect.height = mousePos.y - m_mouseRect.y;
        }
        DrawRectangleLinesEx(m_mouseRect, 1.0f, GREEN);
    }
}
