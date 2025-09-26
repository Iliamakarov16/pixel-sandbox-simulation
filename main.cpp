#include <raylib.h>

int main() {
    const int windowHeight = 1920;
    const int windowWidth = 1080;
    InitWindow(windowWidth, windowHeight, "Pixel Simulation");
    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}