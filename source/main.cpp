#include <buildings/Castle.h>
#include <units/Villager.h>
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

    std::shared_ptr<Castle> castle = std::make_shared<Castle>();

    std::vector<std::shared_ptr<Villager>> villagers;
    villagers.emplace_back(std::make_shared<Villager>());
    villagers.emplace_back(std::make_shared<Villager>());

    villagers[0]->SetCurrentPosition(100, 100);
    villagers[1]->SetCurrentPosition(200, 300);

    String curr = "Label is empty";
    while (!WindowShouldClose()) {
        const Vector2 mousePos      = GetMousePosition();
        const bool    bMouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if (!castle->IsPlaced() && bMouseClicked) {
            castle->SetPositionFromMouse(mousePos);
            castle->SetPlaced(true);
        } else if (!castle->IsPlaced()) {
            castle->SetPositionFromMouse(mousePos);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        castle->Process(mousePos);
        std::for_each(villagers.begin(),
                      villagers.end(),
                      [&mousePos](const std::shared_ptr<Villager>& villager) {
                          villager->Process(mousePos);
                      });

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
