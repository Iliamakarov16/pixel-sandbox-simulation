#include "Grid.hpp"

void Grid::draw() const{
    for (int row = 0; row < rows_; row++){
        for (int col = 0; col < columns_; col++){
            DrawRectangle(row * cellSize_, col * cellSize_, cellSize_, cellSize_, cells_[row][col].color);
        }
    }
}

    bool Grid::isValidCell(const int& row, const int& column) const{
        if ((row < rows_ && row >= 0) && (column < columns_ && column >= 0)) return true;
        return false;
    }

    void Grid::setCell(const int& row, const int& column, const SimMaterial& material){
        if (isValidCell(row, column) && cells_[row][column].id == EMPTY){
            cells_[row][column] = material; 
        }
    }

    SimMaterial Grid::getCell(const int& row, const int& column) const{
        if (!isValidCell(row, column)){
            throw std::out_of_range("Cell is out of bound.");
        }
        return cells_[row][column];
    }