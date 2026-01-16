#include "Game.hpp"

//Holding left mouse button sets current material to cell. Holding right mouse buttom makes cell empty
void Game::mouseControlls(){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        Vector2 mousePos = GetMousePosition();
        int mousePosRow = mousePos.y / sim.getCellSize();
        int mousePosCol = mousePos.x / sim.getCellSize();
        sim.setCell(mousePosRow, mousePosCol, currentMaterial);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        Vector2 mousePos = GetMousePosition();
        int mousePosRow = mousePos.y / sim.getCellSize();
        int mousePosCol = mousePos.x / sim.getCellSize();
        sim.setCell(mousePosRow, mousePosCol, MATERIALS[EMPTY]);
    }
}

void Game::gameControlls(){
    mouseControlls();
}