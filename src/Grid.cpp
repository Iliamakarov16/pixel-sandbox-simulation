#include "Grid.hpp"

void Grid::draw() const{
    for (int row = 0; row < rows_; row++){
        for (int col = 0; col < cols_; col++){
            DrawRectangle(col * cellSize_, row * cellSize_, cellSize_, cellSize_, cells_[row][col].color);
        }
    }
}

bool Grid::isValidCell(const int& row, const int& col) const{
    return ((row < rows_ && row >= 0) && (col < cols_ && col >= 0));
}

void Grid::setCell(const int& row, const int& col, const SimMaterial& material){
    if (isValidCell(row, col) && cells_[row][col].id == EMPTY){
        cells_[row][col] = material; 
    }
    else if (isValidCell(row, col) && material.id == EMPTY){//allows setting empty
        cells_[row][col] = material;
    }
}

SimMaterial Grid::getCell(const int& row, const int& col) const{
    if (!isValidCell(row, col)){
        return getMaterial(EMPTY);
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

bool Grid::isEmptyCell(const int& row, const int& col) const{
    return isValidCell(row, col) && cells_[row][col].id == EMPTY;
}

void Grid::swapCells(const int& row_1, const int& col_1, const int& row_2, const int& col_2){
    std::swap(cells_[row_1][col_1], cells_[row_2][col_2]);
}