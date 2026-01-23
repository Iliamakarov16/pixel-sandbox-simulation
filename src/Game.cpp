#include "Game.hpp"

void Game::changeBrushSize(){
    float wheel = GetMouseWheelMove();
    
    if (wheel > 0){//Scroll up increases brush size
        brushSize += (int)wheel;
        std::cout << brushSize << '\n';
    }
    if (wheel < 0 && brushSize > 1){//Scroll down decreases brush size
        brushSize += (int)wheel;
        std::cout << brushSize << '\n';
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) || brushSize < 1){
        brushSize = 1;
        std::cout << brushSize << '\n';
    }
}

void Game::drawSquareBrush(){
    Vector2 mousePos = GetMousePosition();
    int mousePosRow = mousePos.y / sim.getCellSize();
    int mousePosCol = mousePos.x / sim.getCellSize();

    //top left corner of square
    int topLeftRow = (mousePosRow - brushSize) * sim.getCellSize() ;
    int topLeftCol = (mousePosCol - brushSize) * sim.getCellSize() ;

    DrawRectangleLines(topLeftCol, topLeftRow, brushSize * sim.getCellSize(), brushSize * sim.getCellSize(), WHITE);
}

void Game::applySquareBrush(){
    Vector2 mousePos = GetMousePosition();
    int mousePosRow = mousePos.y / sim.getCellSize();
    int mousePosCol = mousePos.x / sim.getCellSize();

    //top left corner of square
    int topLeftRow = mousePosRow - brushSize;
    int topLeftCol = mousePosCol - brushSize;

    if (brushSize == 1){
        sim.setCell(topLeftRow, topLeftCol, currentMaterial);
    }
    else{
        for (int row = topLeftRow; row < mousePosRow; row++){
            for (int col = topLeftCol; col < mousePosCol; col++){
                sim.setCell(row, col, currentMaterial);
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


// void Game::applyBrush(){}

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
    if (IsKeyPressed(KEY_F1)){
        currentMaterial = getMaterial(SAND);
    }
    if (IsKeyPressed(KEY_F2)){
        currentMaterial = getMaterial(WATER);
    }
    if (IsKeyPressed(KEY_F3)){
        currentMaterial = getMaterial(STEAM);
    }
    if (IsKeyPressed(KEY_F4)){
        currentMaterial = getMaterial(STONE);
    }
    if (IsKeyPressed(KEY_LEFT_BRACKET)){
        if (ticksPerSecond > 0){
            ticksPerSecond -= 1;
        }
        else{
            ticksPerSecond = 0;
        }
    }
    if (IsKeyPressed(KEY_RIGHT_BRACKET)){
        ticksPerSecond++;
    }
    if (IsKeyPressed(KEY_O)){
        isCircleBrush = !isCircleBrush;
    }
}

void Game::gameControls(){
    menu_.update();
    mouseControls();
    keyboardControls();
    changeBrushSize();
}

void Game::draw(){
    sim.draw();
    if (!isCircleBrush){
        drawSquareBrush();
    }
    else{
        drawCircleBrush();
    }
    menu_.draw();
    DrawText(TextFormat("TPS: %.0f", ticksPerSecond), 0, GetScreenHeight() - 20, 20, WHITE);
}

void Game::update(){
    while (tickTriggered()){
        sim.simulate();
    }
}

bool Game::tickTriggered(){
    const double currTime = GetTime();
    if (ticksPerSecond <= 0.0){
        return false;
    }

    const double tickInterval = 1.0 / ticksPerSecond;
    if (currTime - lastUpdateTime >= tickInterval){
        lastUpdateTime += tickInterval;
        return true;
    }
    return false;
}
