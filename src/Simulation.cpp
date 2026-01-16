#include "Simulation.hpp"

void Simulation::simulateGranular(const int& row, const int& col, const SimMaterial& material){
    const int bottomCol = row + neighborsOffset[BOTTOM].second;
    const int bottomRow = col + neighborsOffset[BOTTOM].first;
    const int leftCol = row + neighborsOffset[BOTTOM_LEFT].second;
    const int leftRow = col + neighborsOffset[BOTTOM_LEFT].first;
    const int rightCol = row + neighborsOffset[BOTTOM_RIGHT].second;
    const int rightRow = col + neighborsOffset[BOTTOM_RIGHT].first;

    if (grid.isValidCell(bottomCol, bottomRow) &&
        grid.getCell(bottomCol, bottomRow).id == EMPTY) {
        tempGrid.setCell(bottomCol, bottomRow, material);
        return;
    }
    else if (grid.isValidCell(leftCol, leftRow) &&
        grid.getCell(leftCol, leftRow).id == EMPTY) {
        tempGrid.setCell(leftCol, leftRow, material);
        return;
    }
    else if (grid.isValidCell(rightCol, rightRow) &&
        grid.getCell(rightCol, rightRow).id == EMPTY) {
        tempGrid.setCell(rightCol, rightRow, material);
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
    for(int row = 0; row < grid.getRows(); row++){
        for(int col = 0; col < grid.getColumns(); col++){
            if (grid.getCell(row, col).type == GRANULAR){
                simulateGranular(row, col, getCell(row, col));
            }
        }
    }
    grid = tempGrid;
}
