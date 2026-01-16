#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "Material.hpp"
#include <utility>

class Simulation {
private:
    Grid grid_;
    Grid tempGrid_;
    std::vector<std::pair<int, int>> neighborsOffset_;

    //Material type physics
    void simulateGranular(const int& row, const int& col, const SimMaterial& material);
    void simulateLiquid(const int& row, const int& col, const SimMaterial& material);
    void simulateGas(const int& row, const int& col, const SimMaterial& material);

    //Material ID collision interaction
    void SandCollisions(const int& row, const int& col, const SimMaterial& Sand);

    void simulatePhysics(const int& row, const int& col);
    void simulateCollisions(const int& row, const int& col);
public:
    Simulation(const int& rows, const int& cols, const int& cellSize) :
    grid_(rows, cols, cellSize),
    tempGrid_(rows, cols, cellSize),
    neighborsOffset_{
        {-1, 0}, // above
        {1, 0},  // below
        {0, 1},  // right
        {0, -1}, // left
        {-1, 1}, // upper right
        {-1, -1}, // upper left
        {1, 1},  // lower right
        {1, -1}  // lower left
    }{};
    
    void simulate();    

    void draw() const{ grid_.draw();}

    void setCell(const int& row, const int& col, const SimMaterial& material)
        {grid_.setCell(row, col, material);}
    SimMaterial getCell(const int& row, const int& col) const
        {return grid_.getCell(row, col);}
    bool isEmptyCell(const int& row, const int& col) const
        {return grid_.isEmptyCell(row, col);}

    void clear(){grid_.clear();}

    int getCellSize() const {return grid_.getCellSize();}
};

enum Directions{//enum for offset
    TOP,
    BOTTOM,
    RIGHT,
    LEFT,
    TOP_RIGHT,
    TOP_LEFT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT
};
