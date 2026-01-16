#include <include/raylib.h>
#include "Simulation.hpp"

int main() 
{
    constexpr int SCREEN_WIDTH = 1200;
    constexpr int SCREEN_HEIGHT = 1200;
    const int CELL_SIZE = 20;
    const int FPS = 1;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pixel sandbox game");
    SetTargetFPS(FPS);
    
    Simulation sim(SCREEN_WIDTH, SCREEN_HEIGHT, CELL_SIZE); 

    sim.setCell(10, 10, MATERIALS[SAND]);

    while (!WindowShouldClose()){
        BeginDrawing();
        sim.simulate();
        ClearBackground(BLACK);
        sim.draw();

        EndDrawing();
    }
    
    CloseWindow();
}
