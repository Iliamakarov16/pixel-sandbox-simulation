#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "Material.hpp"
#include <utility>

class Simulation {
private:
    Grid grid;
    Grid tempGrid;
    std::vector<std::pair<int, int>> neighborsOffset;

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
    grid(rows, cols, cellSize),
    tempGrid(rows, cols, cellSize),
    neighborsOffset{
        {-1, 0}, // above
        {1, 0},  // below
        {0, 1},  // right
        {0, -1}, // left
        {-1, 1}, // upper right
        {-1, -1}, // upper left
        {1, 1},  // lower right
        {1, -1}  // lower left
    }{};

    void draw() const{ grid.draw();}
    void simulate();

    void setCell(const int& row, const int& col, const SimMaterial& material)
        {grid.setCell(row, col, material);}
    SimMaterial getCell(const int& row, const int& col) const
        {return grid.getCell(row, col);}
    bool isValidCell(const int& row, const int& col) const
        {return grid.isValidCell(row, col);};
    int getCellSize() const {return grid.getCellSize();}

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
