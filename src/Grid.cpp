#include "Grid.hpp"

void Grid::draw() const{
    for (int row = 0; row < rows_; row++){
        for (int col = 0; col < cols_; col++){
            DrawRectangle(col * cellSize_, row * cellSize_, cellSize_, cellSize_, cells_[row][col].color);
        }
    }
}

bool Grid::isValidCell(const int& row, const int& col) const{
    if ((row < rows_ && row >= 0) && (col < cols_ && col >= 0)) return true;
    return false;
}

void Grid::setCell(const int& row, const int& col, const SimMaterial& material){
    if (isValidCell(row, col) && cells_[row][col].id == EMPTY){
        cells_[row][col] = material; 
    }
}

SimMaterial Grid::getCell(const int& row, const int& col) const{
    if (!isValidCell(row, col)){
        throw std::out_of_range("Cell is out of bound.");
    }
    return cells_[row][col];
}

void Grid::clear(){
    for (int row = 0; row < rows_; row++){
        for (int col = 0; col < cols_; col++){
            cells_[row][col] = getMaterial(EMPTY);
        }
    }
}
