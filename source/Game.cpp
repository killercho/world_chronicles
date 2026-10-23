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
    const Vector2 mousePos           = GetMousePosition();
    const bool    bMouseClicked      = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    const bool    bRightClickClicked = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
    const bool    bMouseReleased     = IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
    DrawMouseRectangle();

    if (!m_castle->IsPlaced() && bMouseClicked) {
        m_castle->SetPositionFromMouse(mousePos);
        m_castle->SetPlaced(true);
    } else if (!m_castle->IsPlaced()) {
        m_castle->SetPositionFromMouse(mousePos);
    }

    if (bRightClickClicked) {
        std::for_each(m_villagers.begin(),
                      m_villagers.end(),
                      [&mousePos](const std::shared_ptr<Villager>& villager) {
                          if (villager->IsSelected()) {
                              villager->MoveTowardMouse(mousePos);
                          }
                      });
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    m_castle->Process(mousePos);
    std::for_each(
        m_villagers.begin(),
        m_villagers.end(),
        [bMouseReleased, this](const std::shared_ptr<Villager>& villager) {
            villager->Process(bMouseReleased, m_mouseRect);
        });

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
