#include "Game.hpp"

void Game::changeBrushSize(){
    float wheel = GetMouseWheelMove();
    
    if (wheel > 0){//Scroll up increases brush size
        brushSize += (int)wheel;
    }
    if (wheel < 0 && brushSize > 1){//Scroll down decreases brush size
        brushSize += (int)wheel;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || brushSize < 1){
        brushSize = 1;
    }
}

void Game::drawSquareBrush(){
    
    Vector2 mousePos = GetMousePosition();
    int cell = sim.getCellSize();
    int mousePosRow = mousePos.y / cell;
    int mousePosCol = mousePos.x / cell;
   
    int half = brushSize / 2;
    int topLeftRow = (mousePosRow - half) * cell;
    int topLeftCol = (mousePosCol - half) * cell;

    DrawRectangleLines(topLeftCol, topLeftRow, brushSize * cell, brushSize * cell, WHITE);
}

void Game::applySquareBrush(){
    Vector2 mousePos = GetMousePosition();
    int mousePosRow = mousePos.y / sim.getCellSize();
    int mousePosCol = mousePos.x / sim.getCellSize();

    if (sim.isValidCell(mousePosRow, mousePosCol)){
        int half = brushSize / 2;
        int topLeftRow = mousePosRow - half;
        int topLeftCol = mousePosCol - half;
        int bottomRow = topLeftRow + brushSize;
        int rightCol = topLeftCol + brushSize;

        if (brushSize == 1){
            sim.setCell(topLeftRow, topLeftCol, currentMaterial);
        }
        else{
            for (int row = topLeftRow; row < bottomRow; row++){
                for (int col = topLeftCol; col < rightCol; col++){
                    sim.setCell(row, col, currentMaterial);
                }
            }
        }
    }
}

void Game::drawCircleBrush(){
    Vector2 mousePos = GetMousePosition();
    int cell = sim.getCellSize();
    int centerRow = mousePos.y / cell;
    int centerCol = mousePos.x / cell;

    int r = brushSize;
    int r2 = r * r;

    for (int row = centerRow - r; row <= centerRow + r; ++row){
        for (int col = centerCol - r; col <= centerCol + r; ++col){
            int dr = row - centerRow;
            int dc = col - centerCol;
            int d2 = dr*dr + dc*dc;
            if (d2 > r2){
                continue;
            }

            // Draw only outer edges for cells inside the circle.
            int left = col * cell;
            int top = row * cell;
            int right = left + cell;
            int bottom = top + cell;

            if ((dr - 1) * (dr - 1) + dc * dc > r2){ // neighbor above is outside
                DrawLine(left, top, right, top, WHITE);
            }
            if ((dr + 1) * (dr + 1) + dc * dc > r2){ // neighbor below is outside
                DrawLine(left, bottom, right, bottom, WHITE);
            }
            if (dr * dr + (dc - 1) * (dc - 1) > r2){ // neighbor left is outside
                DrawLine(left, top, left, bottom, WHITE);
            }
            if (dr * dr + (dc + 1) * (dc + 1) > r2){ // neighbor right is outside
                DrawLine(right, top, right, bottom, WHITE);
            }
        }
    }
}

void Game::applyCircleBrush(){
    
    Vector2 mousePos = GetMousePosition();
    int centerRow = mousePos.y / sim.getCellSize();
    int centerCol = mousePos.x / sim.getCellSize();

    if (sim.isValidCell(centerRow, centerCol)){
        int r = brushSize;
        int r2 = r * r;

        for (int row = centerRow - r; row <= centerRow + r; ++row){
            for (int col = centerCol - r; col <= centerCol + r; ++col){
                int dr = row - centerRow;
                int dc = col - centerCol;
                if (dr*dr + dc*dc <= r2){
                    sim.setCell(row, col, currentMaterial);
                }
            }
        }
    }
}

//Holding left mouse button sets current material to cell. Holding right mouse buttom makes cell empty
void Game::mouseControls(){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !isCircleBrush){
        applySquareBrush();
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        applyCircleBrush();
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !isCircleBrush){//eraser
        SimMaterial lastCurrMat = currentMaterial;
        currentMaterial = getMaterial(EMPTY);
        applySquareBrush();
        currentMaterial = lastCurrMat;
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        SimMaterial lastCurrMat = currentMaterial;
        currentMaterial = getMaterial(EMPTY);
        applyCircleBrush();
        currentMaterial = lastCurrMat;
    }
}


void Game::keyboardControls(){
    if (IsKeyPressed(KEY_C)){//C clears grid
        sim.clear();
    }
    if (IsKeyPressed(KEY_LEFT_BRACKET)){
        if (fps > 0){
            fps--;
            SetTargetFPS(fps);
        }
        else{
            fps = 0;
            SetTargetFPS(fps);
        }
    }
    if (IsKeyPressed(KEY_RIGHT_BRACKET)){
        fps++;
        SetTargetFPS(fps);
    }
    if (IsKeyPressed(KEY_O)){
        isCircleBrush = !isCircleBrush;
    }
}

void Game::drawCellInfo(){
    Vector2 mousePos = GetMousePosition();
    int mousePosRow = mousePos.y / sim.getCellSize();
    int mousePosCol = mousePos.x / sim.getCellSize();

    if (!sim.isValidCell(mousePosRow, mousePosCol)) {
        return;
    }

    std::string matName = sim.getCell(mousePosRow, mousePosCol).name;
    const char* matNameC = matName.c_str();
    int nameTextSize = MeasureText(TextFormat("Material: %s", matNameC), 15);
    DrawText(TextFormat("Material: %s", matNameC), 60, GetScreenHeight() - 20, 15, WHITE);

    int temp = sim.getCellTemperature(mousePosRow, mousePosCol);
    DrawText(TextFormat("Temperature: %i", temp), 70 + nameTextSize, GetScreenHeight() - 20, 15, WHITE);
}

void Game::gameControls(){
    if (!isGameActive && startButton.isClicked()) {
        sim.removeStone();
        startButton.onClick();
        return;
    }
    menu_.update();
    if (!isGameActive){
       mouseControls(); 
    }
        
    keyboardControls();
    changeBrushSize();
}

void Game::draw(){
    sim.draw();
    if (isGameActive){
        if (!isCircleBrush){
            drawSquareBrush();
        }
        else{
            drawCircleBrush();
        }
    }
    
    
    menu_.draw();

    if (!isGameActive){
        startButton.draw();
    }   

    DrawText(TextFormat("FPS: %i", fps), 0, GetScreenHeight() - 20, 15, WHITE);//Draw FPS
    drawCellInfo();
}

void Game::update(){
    fps = GetFPS();
    sim.simulate();
}

bool Game::eventTriggered(double interval){
    double currTime = GetTime();

    if (currTime - lastUpdateTime >= interval){
        lastUpdateTime = currTime;
        return true;
    }
    return false;
} 
