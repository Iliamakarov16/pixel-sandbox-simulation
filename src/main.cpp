#include "include/raylib.h"
#include "Game.hpp"

int main() 
{
    constexpr int SCREEN_WIDTH = 1200;
    constexpr int SCREEN_HEIGHT = 1000;
    constexpr int CELL_SIZE = 5;
    constexpr int FPS = 60;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pixel sandbox game");
    SetTargetFPS(FPS);
    
    
    Game game(SCREEN_HEIGHT, SCREEN_WIDTH, CELL_SIZE); 

    while (!WindowShouldClose()){
        if (IsWindowResized())
        BeginDrawing();

        game.update();
        game.gameControls();

        ClearBackground(BLACK);

        game.draw();

        EndDrawing();
    }
    
    CloseWindow();
}
