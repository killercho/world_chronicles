#include "Constants.h"

#include <raylib.h>

int main() {
    InitWindow(general_settings::SCREEN_WIDTH,
               general_settings::SCREEN_HEIGHT,
               general_settings::TITLE);
    SetTargetFPS(general_settings::TARGET_FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a basic raylib window", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
