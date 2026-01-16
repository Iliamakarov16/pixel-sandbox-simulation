#pragma once

#include "include/raylib.h"
#include "Material.hpp"
#include <vector>
#include <stdexcept>

class Grid{
private:
    int rows_;
    int columns_;
    int cellSize_;
    std::vector<std::vector<SimMaterial>> cells_;
public:
    Grid(const int& rows, const int& columns, const int& cellSize) 
    : rows_(rows / cellSize),
      columns_(columns / cellSize),
      cellSize_(cellSize),
      cells_(rows_, std::vector<SimMaterial>(columns_, getMaterial(EMPTY))){}; 
    
    void draw() const;

    bool isValidCell(const int& row, const int& column) const;

    void setCell(const int& row, const int& column, const SimMaterial& material);
    SimMaterial getCell(const int& row, const int& column) const;

    
};