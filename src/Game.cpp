#include "Game.hpp"

//Holding left mouse button sets current material to cell. Holding right mouse buttom makes cell empty
void Game::mouseControls(){
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

        sim.setCell(mousePosRow, mousePosCol, getMaterial(EMPTY));
    }
}

void Game::keyboardControls(){
    if (IsKeyPressed(KEY_C)){//C clears grid
        sim.clear();
    }
    if (IsKeyPressed(KEY_F1)){
        currentMaterial = getMaterial(SAND);
    }
    if (IsKeyPressed(KEY_F2)){
        currentMaterial = getMaterial(WATER);
    }
    if (IsKeyPressed(KEY_F3)){
        currentMaterial = getMaterial(VAPOR);
    }
    if (IsKeyPressed(KEY_F4)){
        currentMaterial = getMaterial(STONE);
    }
}

void Game::gameControls(){
    mouseControls();
    keyboardControls();
}