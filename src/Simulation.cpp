#include "Simulation.hpp"

//checks if one of bottom neighbors is empty, and sets material to new position if true. 
void Simulation::simulateGranular(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset_[BOTTOM].first;
    const int bottomCol = col + neighborsOffset_[BOTTOM].second;
    const int bLeftRow = row + neighborsOffset_[BOTTOM_LEFT].first;
    const int bLeftCol = col + neighborsOffset_[BOTTOM_LEFT].second;
    const int bRightRow = row + neighborsOffset_[BOTTOM_RIGHT].first;
    const int bRightCol = col + neighborsOffset_[BOTTOM_RIGHT].second;

    auto isLiquidCell = [&](const int& a, const int& b){
        return grid_.getCell(a, b).type == LIQUID;
    };

    if (isEmptyForSim(bottomRow, bottomCol)) {
        tempGrid_.setCell(bottomRow, bottomCol, material);
        return;
    }
    else if (isEmptyForSim(bLeftRow, bLeftCol)) {
        tempGrid_.setCell(bLeftRow, bLeftCol, material);
        return;
    }
    else if (isEmptyForSim(bRightRow, bRightCol)) {
        tempGrid_.setCell(bRightRow, bRightCol, material);
        return;
    }
    else if (isLiquidCell(bottomRow, bottomCol)){
        if (GetRandomValue(0, 3) == 0) {
            liquidDisplacement(row, col, bottomRow, bottomCol);
        }
    }

    tempGrid_.setCell(row, col, material);
}

void Simulation::liquidDisplacement(const int& row_1, const int& col_1, const int& row_2, const int& col_2){
    tempGrid_.setCell(row_1, col_1, getCell(row_1, col_1));
    tempGrid_.setCell(row_2, col_2, getCell(row_2, col_2));
    tempGrid_.swapCells(row_1, col_1, row_2, col_2);
    return;
}

void Simulation::simulateLiquid(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset_[BOTTOM].first;
    const int bottomCol = col + neighborsOffset_[BOTTOM].second;
    const int bLeftRow = row + neighborsOffset_[BOTTOM_LEFT].first;
    const int bLeftCol = col + neighborsOffset_[BOTTOM_LEFT].second;
    const int bRightRow = row + neighborsOffset_[BOTTOM_RIGHT].first;
    const int bRightCol = col + neighborsOffset_[BOTTOM_RIGHT].second;
    const int leftRow = row + neighborsOffset_[LEFT].first;
    const int leftCol = col + neighborsOffset_[LEFT].second;
    const int rightRow = row + neighborsOffset_[RIGHT].first;
    const int rightCol = col + neighborsOffset_[RIGHT].second;
    
    int desiredVx = liquidVx_[row][col];
    if (desiredVx == 0) {
        desiredVx = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    }

    if (isEmptyForSim(bottomRow, bottomCol)) {
        tempGrid_.setCell(bottomRow, bottomCol, material);
        tempLiquidVx_[bottomRow][bottomCol] = desiredVx;
        return;
    }
    //Water bounce: when the preferred diagonal is blocked, flip horizontal direction.
    if (desiredVx < 0) {
        if (isEmptyForSim(bLeftRow, bLeftCol)) {
            tempGrid_.setCell(bLeftRow, bLeftCol, material);
            tempLiquidVx_[bLeftRow][bLeftCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(bRightRow, bRightCol)) {
            desiredVx = 1;
            tempGrid_.setCell(bRightRow, bRightCol, material);
            tempLiquidVx_[bRightRow][bRightCol] = desiredVx;
            return;
        }
    } else {
        if (isEmptyForSim(bRightRow, bRightCol)) {
            tempGrid_.setCell(bRightRow, bRightCol, material);
            tempLiquidVx_[bRightRow][bRightCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(bLeftRow, bLeftCol)) {
            desiredVx = -1;
            tempGrid_.setCell(bLeftRow, bLeftCol, material);
            tempLiquidVx_[bLeftRow][bLeftCol] = desiredVx;
            return;
        }
    }
    //Water bounce: when blocked to the left, tries the opposite side.
    if (desiredVx < 0) {
        if (isEmptyForSim(leftRow, leftCol)) {
            tempGrid_.setCell(leftRow, leftCol, material);
            tempLiquidVx_[leftRow][leftCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(rightRow, rightCol)) {
            desiredVx = 1;
            tempGrid_.setCell(rightRow, rightCol, material);
            tempLiquidVx_[rightRow][rightCol] = desiredVx;
            return;
        }
    } else {//Water bounce: when blocked to the right, tries the opposite side.
        if (isEmptyForSim(rightRow, rightCol)) {
            tempGrid_.setCell(rightRow, rightCol, material);
            tempLiquidVx_[rightRow][rightCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(leftRow, leftCol)) {
            desiredVx = -1;
            tempGrid_.setCell(leftRow, leftCol, material);
            tempLiquidVx_[leftRow][leftCol] = desiredVx;
            return;
        }
    }

    tempGrid_.setCell(row, col, material);
    tempLiquidVx_[row][col] = desiredVx;
}

void Simulation::simulateGas(const int& row, const int& col, const SimMaterial& material){
    const int topRow = row + neighborsOffset_[TOP].first;
    const int topCol = col + neighborsOffset_[TOP].second;
    const int tLeftRow = row + neighborsOffset_[TOP_LEFT].first;
    const int tLeftCol = col + neighborsOffset_[TOP_LEFT].second;
    const int tRightRow = row + neighborsOffset_[TOP_RIGHT].first;
    const int tRightCol = col + neighborsOffset_[TOP_RIGHT].second;
    const int leftRow = row + neighborsOffset_[LEFT].first;
    const int leftCol = col + neighborsOffset_[LEFT].second;
    const int rightRow = row + neighborsOffset_[RIGHT].first;
    const int rightCol = col + neighborsOffset_[RIGHT].second;
    
    int desiredVx = gasVx_[row][col];
    if (desiredVx == 0) {
        desiredVx = (GetRandomValue(0, 1) == 0) ? -1 : 1;
    }

    const bool allowRise = (GetRandomValue(0, 4) != 0);
    if (allowRise) {
        if (isEmptyForSim(topRow, topCol)) {
            tempGrid_.setCell(topRow, topCol, material);
            tempGasVx_[topRow][topCol] = desiredVx;
            return;
        }
    }

    //Gas bounce: when the preferred diagonal is blocked, flip horizontal direction.
    if (desiredVx < 0){
        if (isEmptyForSim(tLeftRow, tLeftCol)) {
            tempGrid_.setCell(tLeftRow, tLeftCol, material);
            tempGasVx_[tLeftRow][tLeftCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(tRightRow, tRightCol)) {
            desiredVx = 1;
            tempGrid_.setCell(tRightRow, tRightCol, material);
            tempGasVx_[tRightRow][tRightCol] = desiredVx;
            return;
        }
    }
    else{
        if (isEmptyForSim(tRightRow, tRightCol)) {
            tempGrid_.setCell(tRightRow, tRightCol, material);
            tempGasVx_[tRightRow][tRightCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(tLeftRow, tLeftCol)) {
            desiredVx = -1;
            tempGrid_.setCell(tLeftRow, tLeftCol, material);
            tempGasVx_[tLeftRow][tLeftCol] = desiredVx;
            return;
        }
    }

    //Slow diffusion: only spread sideways occasionally to keep clouds cohesive.
    if (GetRandomValue(0, 3) == 0) {
    if (desiredVx < 0) {
        if (isEmptyForSim(leftRow, leftCol)) {
            tempGrid_.setCell(leftRow, leftCol, material);
            tempGasVx_[leftRow][leftCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(rightRow, rightCol)) {
            desiredVx = 1;
            tempGrid_.setCell(rightRow, rightCol, material);
            tempGasVx_[rightRow][rightCol] = desiredVx;
            return;
        }
    } else {//Gas bounce: when blocked to the right, tries the opposite side.
        if (isEmptyForSim(rightRow, rightCol)) {
            tempGrid_.setCell(rightRow, rightCol, material);
            tempGasVx_[rightRow][rightCol] = desiredVx;
            return;
        } 
        else if (isEmptyForSim(leftRow, leftCol)) {
            desiredVx = -1;
            tempGrid_.setCell(leftRow, leftCol, material);
            tempGasVx_[leftRow][leftCol] = desiredVx;
            return;
        }
    }
    }
    
    
    tempGrid_.setCell(row, col, material);
    tempGasVx_[row][col] = desiredVx;
}

void Simulation::simulateSolid(const int& row, const int& col, const SimMaterial& material){
    tempGrid_.setCell(row, col, material);
}

void Simulation::simulatePhysics(){
    //clear temps
    tempGrid_.clear();
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            tempLiquidVx_[row][col] = 0;
        }
    }
    for (int row = 0; row < grid_.getRows(); row++){
        for (int col = 0; col < grid_.getColumns(); col++){
            tempGasVx_[row][col] = 0;
        }
    }
    //simulate
    for(int row = 0; row < grid_.getRows(); row++){
        for(int col = 0; col < grid_.getColumns(); col++){
            if (grid_.getCell(row, col).type == GRANULAR){
                simulateGranular(row, col, getCell(row, col));
            }
            else if (grid_.getCell(row, col).type == LIQUID){
                simulateLiquid(row, col, getCell(row, col));
            }
            else if (grid_.getCell(row, col).type == GAS){
                simulateGas(row, col, getCell(row, col));
            }
            else if (grid_.getCell(row, col).type == SOLID){
                simulateSolid(row, col, getCell(row, col));
            }
        }
    }
    //sets temps
    grid_ = tempGrid_;
    liquidVx_ = tempLiquidVx_;
    gasVx_ = tempGasVx_;
}
// void Simulation::SandInteractions();

void Simulation::simulate(){
    simulatePhysics();
}