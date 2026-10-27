#include "Game.h"
#include <raygui.h>
#include <raylib.h>

Game::Game()
    : m_generalParser(CONSTANTS_PATH "GeneralSettings.ini"),
      m_gameObjectManager(std::make_shared<GameObjectManager>()) { }

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

    CreateButtonMappingText();

    m_gameObjectManager->ProcessBuildings(mousePos, bLeftMouseClicked);
    m_gameObjectManager->ProcessUnits(m_mouseDraggingRect, bLeftMouseReleased);

    EndDrawing();
}

void Game::DrawMouseRectangle() {
    const Vector2 mousePos      = GetMousePosition();
    const bool    bMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (bMouseClicked) {
        m_mouseStartPos.x = mousePos.x;
        m_mouseStartPos.y = mousePos.y;
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (m_mouseStartPos.x > mousePos.x) {
            m_mouseDraggingRect.x = mousePos.x;
        } else {
            m_mouseDraggingRect.x = m_mouseStartPos.x;
        }
        if (m_mouseStartPos.y > mousePos.y) {
            m_mouseDraggingRect.y = mousePos.y;
        } else {
            m_mouseDraggingRect.y = m_mouseStartPos.y;
        }
        m_mouseDraggingRect.width  = std::abs(m_mouseStartPos.x - mousePos.x);
        m_mouseDraggingRect.height = std::abs(m_mouseStartPos.y - mousePos.y);
        DrawRectangleLinesEx(m_mouseDraggingRect, 1.0f, GREEN);
    }
}

void Game::CreateButtonMappingText() {
    GuiLabel(Rectangle(300, 50, 300, 50),
             "Press 'V' to spawn villagers in the top left courner");
    GuiLabel(Rectangle(300, 100, 300, 50),
             "Press 'C' to spawn castles on the mouse cursor");
}
