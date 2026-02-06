#include "include/raylib.h"
#include "Game.hpp"

int main() 
{
    int screenWidth = 1400;
    int screenHeight = 1000;
    constexpr int CELL_SIZE = 10;
    constexpr int FPS = 45;
    
    InitWindow(screenWidth, screenHeight, "Pixel sandbox");
    SetTargetFPS(FPS);
    
    Game game(screenHeight, screenWidth, CELL_SIZE); 

    game.setTitleGrid();

    while (!WindowShouldClose()){
        BeginDrawing();
        game.gameControls();
        if (game.isGameActive){
            game.update();
            
            ClearBackground(BLACK);
        }
        
        game.draw();

        EndDrawing();
    }
    
    CloseWindow();
}
