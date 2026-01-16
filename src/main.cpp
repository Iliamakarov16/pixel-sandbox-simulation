#include <include/raylib.h>
#include "Grid.hpp"

int main() 
{
    constexpr int SCREEN_WIDTH = 1200;
    constexpr int SCREEN_HEIGHT = 1200;
    const int CELL_SIZE = 20;
    const int FPS = 30;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pixel sandbox game");
    SetTargetFPS(FPS);
    
    Grid grid(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE); 

    while (!WindowShouldClose()){
        BeginDrawing();
        
        ClearBackground(BLACK);
        grid.draw();

        EndDrawing();
    }
    
    CloseWindow();
}
