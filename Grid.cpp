#include "Grid.hpp"

void Grid::draw(){
    for (int row = 0; row < rows_; row++){
        for(int col = 0; col < columns_; col++){
            Color color = cells_[row][col] ? GREEN : Color{40, 40, 40, 255};
            DrawRectangle(row * cellSize_, col * cellSize_, cellSize_ - 1, cellSize_ - 1, color);
        }
    }
}

void Grid::setValue(const int& row, const int&  col, const bool&  val){
    if (isValidCell(row, col)){
        cells_[row][col] = val;
    }
}

bool Grid::getValue(const int& row, const int& col) const{
    if (isValidCell(row, col)){
        return cells_[row][col];
    }

    return false;
}

bool Grid::isValidCell(const int&  row, const int&  col) const{
    return row >= 0 && row < rows_ && col >= 0 && col < columns_;
}

void Grid::fillRand(){
    for (int row = 0; row < rows_; row++){
        for (int col = 0; col < columns_; col++){
            int randVal = GetRandomValue(0, 4);
            cells_[row][col] = (randVal == 4);
        }
    }
}

void Grid::clear(){
    for (int row = 0; row < rows_; row++){
        for (int col = 0; col < columns_; col++){
            cells_[row][col] = 0;
        }
    }
}

void Grid::toggleCell(const int& row, const int& col){
    if (isValidCell(row / cellSize_, col / cellSize_)){
        cells_[row / cellSize_][col / cellSize_] = !cells_[row / cellSize_][col / cellSize_];
    }
    
}
