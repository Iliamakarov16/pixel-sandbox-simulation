#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "Material.hpp"
#include "utility"

class Simulation {
private:
    Grid grid;
    Grid tempGrid;
    std::vector<std::pair<int, int>> neighborsOffset;
    
    void simulateGranular(const int& row, const int& col, const SimMaterial& material);
    void simulateLiquid(const int& row, const int& col, const SimMaterial& material);
    void simulateGas(const int& row, const int& col, const SimMaterial& material);

    void simulatePhysics(const int& row, const int& col);
    void simulateCollisions(const int& row, const int& col);
public:
    Simulation(const int& rows, const int& cols, const int& cellSize) :
    grid(rows, cols, cellSize),
    tempGrid(rows, cols, cellSize),
    neighborsOffset{
        {0, 1},  // above
        {0, -1}, // below
        {1, 0},  // right
        {-1, 0}, // left
        {1, 1},  // upper right
        {-1, 1}, // upper left
        {1, -1}, // lower right
        {-1, -1} // lower left
    }{};

    void draw() const{ grid.draw();}

    void simulate();

    void setCell(const int& row, const int& col, const SimMaterial& material)
        {grid.setCell(row, col, material);}
    SimMaterial getCell(const int& row, const int& col) const
        {return grid.getCell(row, col);}
    bool isValidCell(const int& row, const int& col) const
        {return grid.isValidCell(row, col);};

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
