#include "Simulation.hpp"

void Simulation::simulateGranular(const int& row, const int& col, const SimMaterial& material){
    const int bottomRow = row + neighborsOffset[BOTTOM].first;
    const int bottomCol = col + neighborsOffset[BOTTOM].second;
    const int leftRow = row + neighborsOffset[BOTTOM_LEFT].first;
    const int leftCol = col + neighborsOffset[BOTTOM_LEFT].second;
    const int rightRow = row + neighborsOffset[BOTTOM_RIGHT].first;
    const int rightCol = col + neighborsOffset[BOTTOM_RIGHT].second;

    if (isValidCell(bottomRow, bottomCol) &&
        getCell(bottomRow, bottomCol).id == EMPTY) {
        tempGrid.setCell(bottomRow, bottomCol, material);
        return;
    }
    else if (isValidCell(leftRow, leftCol) &&
        getCell(leftRow, leftCol).id == EMPTY) {
        tempGrid.setCell(leftRow, leftCol, material);
        return;
    }
    else if (isValidCell(rightRow, rightCol) &&
        getCell(rightRow, rightCol).id == EMPTY) {
        tempGrid.setCell(rightRow, rightCol, material);
        return;
    }

    tempGrid.setCell(row, col, material);
}
// void Simulation::simulateLiquid(const int& row, const int& col, const SimMaterial& material);
// void Simulation::simulateGas(const int& row, const int& col, const SimMaterial& material);



// void Simulation::simulatePhRowsics(const int& row, const int& col){
//     if ()
// }
void Simulation::simulate(){
    tempGrid.clear();
    for(int row = 0; row < grid.getRows(); row++){
        for(int col = 0; col < grid.getColumns(); col++){
            if (grid.getCell(row, col).type == GRANULAR){
                simulateGranular(row, col, getCell(row, col));
            }
        }
    }
    grid = tempGrid;
}
