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

    m_castle    = std::make_shared<Castle>();
    m_villagers = { std::make_shared<Villager>(),
                    std::make_shared<Villager>() };
    m_villagers[0]->SetCurrentPosition(100, 100);
    m_villagers[1]->SetCurrentPosition(200, 100);
}

bool Game::ShouldExit() const {
    return WindowShouldClose();
}

void Game::Process() {
    const Vector2 mousePos      = GetMousePosition();
    const bool    bMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (!m_castle->IsPlaced() && bMouseClicked) {
        m_castle->SetPositionFromMouse(mousePos);
        m_castle->SetPlaced(true);
    } else if (!m_castle->IsPlaced()) {
        m_castle->SetPositionFromMouse(mousePos);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_castle->Process(mousePos);
    std::for_each(m_villagers.begin(),
                  m_villagers.end(),
                  [&mousePos](const std::shared_ptr<Villager>& villager) {
                      villager->Process(mousePos);
                  });

    EndDrawing();
}
