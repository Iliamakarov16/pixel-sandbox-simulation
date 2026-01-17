#include <include/raylib.h>
#include "Game.hpp"

int main() 
{
    constexpr int SCREEN_WIDTH = 1200;
    constexpr int SCREEN_HEIGHT = 1200;
    const int CELL_SIZE = 20;
    const int FPS = 30;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pixel sandbox game");
    SetTargetFPS(FPS);
    
    Game game(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE); 

    while (!WindowShouldClose()){
        BeginDrawing();

        game.simulation();
        game.gameControls();

        ClearBackground(BLACK);

        game.draw();

        EndDrawing();
    }
    
    CloseWindow();
}
