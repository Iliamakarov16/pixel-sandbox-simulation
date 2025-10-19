#include <raylib.h>

int main() 
{   
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    //Game loop
    while (!WindowShouldClose())
    {
        //Event handling and logic  
        
        //Update position

        //Drawing
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }
    
    CloseWindow();
}