#include <Constants.h>
#include <buildings/Castle.h>

#include <raylib.h>

#include <memory>

int main() {
    InitWindow(general_settings::SCREEN_WIDTH,
               general_settings::SCREEN_HEIGHT,
               general_settings::TITLE);
    SetTargetFPS(general_settings::TARGET_FPS);

    // TODO: Create a basic castle and check the spawning and UI
    // std::shared_ptr<Castle> castleTest = std::make_shared<Castle>();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a basic raylib window", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
