#include <buildings/Castle.h>
#include <string/String.h>
#include <parsers/GeneralParser.h>
#include <raygui/raygui.h>
#include <raylib.h>

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

    std::shared_ptr<Castle> castleTest = std::make_shared<Castle>();

    String curr = "Label is empty";
    while (!WindowShouldClose()) {
        const Vector2 mousePos      = GetMousePosition();
        const bool    bMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (!castleTest->IsPlaced() && bMouseClicked) {
            castleTest->SetPositionFromMouse(mousePos);
            castleTest->SetPlaced(true);
        } else if (!castleTest->IsPlaced()) {
            castleTest->SetPositionFromMouse(mousePos);
        }

        if (bMouseClicked &&
            CheckCollisionPointRec(mousePos, castleTest->GetRectangle())) {
            castleTest->SetSelected(true);
        } else if (bMouseClicked) {
            castleTest->SetSelected(false);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        castleTest->Process(mousePos);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
