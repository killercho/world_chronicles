#include <buildings/Castle.h>
#include <string/String.h>
#include <parsers/GeneralParser.h>
#include <raygui/raygui.h>
#include <raylib.h>

#include <iostream>

int main() {
    GeneralParser windowSettings(CONSTANTS_PATH "GeneralSettings.ini");
    if (!windowSettings.GetLatestError().Empty()) {
        throw std::runtime_error("Error when parsing the window settings: " +
                                 windowSettings.GetLatestError().GetData());
    }
    InitWindow(windowSettings.GetWidth(),
               windowSettings.GetHeight(),
               windowSettings.GetTitle().c_str());
    SetTargetFPS(windowSettings.GetTargetFps());
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // TODO: Create a basic castle and check the spawning and UI
    std::shared_ptr<Castle> castleTest = std::make_shared<Castle>();

    String curr = "Label is empty";
    while (!WindowShouldClose()) {
        const Vector2 mousePos = GetMousePosition();
        if (!castleTest->IsPlaced() &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            castleTest->SetCurrentPosition(mousePos);
            castleTest->SetPlaced(true);
        } else if (!castleTest->IsPlaced()) {
            castleTest->SetCurrentPosition(mousePos);
        }

        const bool bMouseOverCastle = CheckCollisionPointRec(mousePos, castleTest->GetRectangle());
        if (bMouseOverCastle && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && castleTest->IsPlaced()) {
            std::cout << String("Castle clicked!\n");
        } 
        if (bMouseOverCastle && castleTest->IsPlaced()) {
            DrawRectangleLinesEx(castleTest->GetRectangle(), 1.0f, GREEN);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        castleTest->Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
