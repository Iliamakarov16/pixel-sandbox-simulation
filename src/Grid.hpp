#pragma once

#include "include/raylib.h"
#include "SimMaterial.hpp"
#include <vector>
#include <stdexcept>

class Grid{
private:
    int rows_;
    int cols_;
    int cellSize_;
    std::vector<std::vector<SimMaterial>> cells_;
public:
    Grid(const int& rows, const int& cols, const int& cellSize) 
    : rows_((rows / cellSize) / 2),
      cols_(cols / cellSize),
      cellSize_(cellSize),
      cells_(rows_, std::vector<SimMaterial>(cols_, getMaterial(EMPTY))){}; 
    
    void draw() const;

    bool isValidCell(const int& row, const int& col) const;
    bool isEmptyCell(const int& row, const int& col) const;

    void setCell(const int& row, const int& col, const SimMaterial& material);
    SimMaterial getCell(const int& row, const int& col) const;
    void clear();

    int getRows() const {return rows_;}
    int getColumns() const {return cols_;}
    int getCellSize() const {return cellSize_;}

    void swapCells(const int& row_1, const int& col_1, const int& row_2, const int& col_2);
};
