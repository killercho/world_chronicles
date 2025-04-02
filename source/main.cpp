#include <raylib.h>

int main() {
    // TODO: Add these constants to a constants sheet with all
    // of the global settings
    const int   SCREEN_WIDTH  = 800;
    const int   SCREEN_HEIGHT = 450;
    const int   TARGET_FPS    = 60;
    const char* TITLE         = "basic window";

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a basic raylib window", 190, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
