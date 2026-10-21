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
    bool                    bPlaced    = false;

    String curr = "Label is empty";
    while (!WindowShouldClose()) {
        const Vector2 mousePos = GetMousePosition();
        if (!bPlaced && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            castleTest->SetCurrentPosition(mousePos);
            castleTest->SetPlaced(true);
            bPlaced = true;
        } else if (!bPlaced) {
            castleTest->SetCurrentPosition(mousePos);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a basic raylib window", 190, 200, 20, BLACK);

        castleTest->Draw();

        GuiLabel(Rectangle(100, 100, 150, 50), curr.c_str());
        if (GuiButton(Rectangle(50, 50, 50, 50), "Click to change the text!")) {
            curr = "Label should be full now";
            std::cout << String("Button was clicked!\n");
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
