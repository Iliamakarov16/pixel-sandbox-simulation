#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "Material.hpp"
#include <vector>
#include <utility>

class Simulation {
private:
    Grid grid_;
    Grid tempGrid_;
    std::vector<std::pair<int, int>> neighborsOffset_;
    //liquid bounce vectors
    std::vector<std::vector<int>> liquidVx_;
    std::vector<std::vector<int>> tempLiquidVx_;
    //Gas behavior 
    std::vector<std::vector<int>> gasVx_;
    std::vector<std::vector<int>> tempGasVx_;

    //Material type physics
    void simulateGranular(const int& row, const int& col, const SimMaterial& material);
    void liquidDisplacement(const int& row_1, const int& col_1, const int& row_2, const int& col_2);
    void simulateLiquid(const int& row, const int& col, const SimMaterial& material);
    void simulateGas(const int& row, const int& col, const SimMaterial& material);
    void simulateSolid(const int& row, const int& col, const SimMaterial& material);
    //Material ID collision interaction
    void SandInteractions(const int& row, const int& col, const SimMaterial& Sand);

    /// @brief Simulates physics for all types of materials 
    void simulatePhysics();
    /// @brief Simulates interactions between materials. e.g when sand interacts with water it becomes wet 
    void simulateInteractions();
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
    }, 
    liquidVx_(rows / cellSize, std::vector<int>(cols / cellSize, 0)),
    tempLiquidVx_(rows / cellSize, std::vector<int>(cols / cellSize, 0)),
    gasVx_(rows / cellSize, std::vector<int>(cols / cellSize, 0)),
    tempGasVx_(rows / cellSize, std::vector<int>(cols / cellSize, 0)) {};
    
    void simulate();    

    void draw() const{ grid_.draw();}

    void setCell(const int& row, const int& col, const SimMaterial& material);

    SimMaterial getCell(const int& row, const int& col) const
        {return grid_.getCell(row, col);}

    void clear(){grid_.clear();}

    bool isEmptyForSim(const int& row, const int& col) 
        {return grid_.isEmptyCell(row, col) && tempGrid_.isEmptyCell(row, col);}

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
