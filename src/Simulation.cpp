#include "Simulation.hpp"

//checks if one of bottom neighbors is empty, and sets material to new position if true. 
void Simulation::simulateGranular(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset_[BOTTOM].first;
    const int bottomCol = col + neighborsOffset_[BOTTOM].second;
    const int bLeftRow = row + neighborsOffset_[BOTTOM_LEFT].first;
    const int bLeftCol = col + neighborsOffset_[BOTTOM_LEFT].second;
    const int bRightRow = row + neighborsOffset_[BOTTOM_RIGHT].first;
    const int bRightCol = col + neighborsOffset_[BOTTOM_RIGHT].second;

    
    if (isEmptyCell(bottomRow, bottomCol)) {
        tempGrid_.setCell(bottomRow, bottomCol, material);
        return;
    }
    else if (isEmptyCell(bLeftRow, bLeftCol)) {
        tempGrid_.setCell(bLeftRow, bLeftCol, material);
        return;
    }
    else if (isEmptyCell(bRightRow, bRightCol)) {
        tempGrid_.setCell(bRightRow, bRightCol, material);
        return;
    }

    tempGrid_.setCell(row, col, material);
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
    
    
    if (isEmptyCell(bottomRow, bottomCol)) {
        tempGrid_.setCell(bottomRow, bottomCol, material);
        return;
    }
    else if (isEmptyCell(bLeftRow, bLeftCol)) {
        tempGrid_.setCell(bLeftRow, bLeftCol, material);
        return;
    }
    else if (isEmptyCell(bRightRow, bRightCol)) {
        tempGrid_.setCell(bRightRow, bRightCol, material);
        return;
    }
    else if (isEmptyCell(leftRow, leftCol)) {
        tempGrid_.setCell(leftRow, leftCol, material);
        return;
    }
    else if (isEmptyCell(rightRow, rightCol)) {
        tempGrid_.setCell(rightRow, rightCol, material);
        return;
    }

    tempGrid_.setCell(row, col, material);
}
// void Simulation::simulateGas(const int& row, const int& col, const SimMaterial& material);


void Simulation::simulate(){
    tempGrid_.clear();
    for(int row = 0; row < grid_.getRows(); row++){
        for(int col = 0; col < grid_.getColumns(); col++){
            if (grid_.getCell(row, col).type == GRANULAR){
                simulateGranular(row, col, getCell(row, col));
            }
            else if (grid_.getCell(row, col).type == LIQUID){
                simulateLiquid(row, col, getCell(row, col));
            }
        }
    }
    grid_ = tempGrid_;
}
