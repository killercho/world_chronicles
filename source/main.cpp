#include <Constants.h>
#include <buildings/Castle.h>

#include <raygui/raygui.h>
#include <raylib.h>

#include <memory>
#include <string>

int main() {
    InitWindow(general_settings::SCREEN_WIDTH,
               general_settings::SCREEN_HEIGHT,
               general_settings::TITLE);
    SetTargetFPS(general_settings::TARGET_FPS);

    // TODO: Create a basic castle and check the spawning and UI
    // std::shared_ptr<Castle> castleTest = std::make_shared<Castle>();

    std::string curr = "Label is empty";
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a basic raylib window", 190, 200, 20, BLACK);

        GuiLabel(Rectangle(100, 100, 150, 50), curr.c_str());
        if (GuiButton(Rectangle(50, 50, 50, 50), "Click to change the text!")) {
            curr = "Label should be full now";
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
