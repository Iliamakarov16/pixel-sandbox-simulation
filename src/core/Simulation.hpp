#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "SimMaterial.hpp"
#include <vector>
#include <utility>
#include <algorithm>

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

    //Physics by material type
    void simulateGranular(const int& row, const int& col, const SimMaterial& material);    
    void simulateLiquid(const int& row, const int& col, const SimMaterial& material);
    void simulateGas(const int& row, const int& col, const SimMaterial& material);
    void simulateSolid(const int& row, const int& col, const SimMaterial& material);
    void simulateCustom(const int& row, const int& col, const SimMaterial& material);

    //Custom physics 
    void wetSandPhysics(const int& row, const int& col, const SimMaterial& wetSand);
    void flamePhysics(const int& row, const int& col, const SimMaterial& flame);
    //Additional behavior
    void steamBehavior(const int& row, const int& col);
    void smokeBehavior(const int& row, const int& col);
    void cloudBehavior(const int& row, const int& col, const SimMaterial& cloud);
    //Interactions by material ID
    void sandInteractions(const int& row, const int& col);
    //Interactions by material type (runs all interactions for material IDs of this type)
    void granularInteractions(const int& row, const int& col, const SimMaterial& material);

    /// @brief Helper for granular material physics
    void liquidDisplacement(const int& row_1, const int& col_1, const int& row_2, const int& col_2);
    /// @brief Applies random color tint for inputed material
    SimMaterial varyColor(SimMaterial material);
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

    /// @brief Runs all the physics and interactions logic
    void simulate();    

    void setCell(const int& row, const int& col, const SimMaterial& material);

    void draw() const
        { grid_.draw();}

    SimMaterial getCell(const int& row, const int& col) const
        {return grid_.getCell(row, col);}

    void clear()
        {grid_.clear();}

    bool isEmptyForSim(const int& row, const int& col) 
        {return grid_.isEmptyCell(row, col) && tempGrid_.isEmptyCell(row, col);}

    bool isValidCell(const int& row, const int& col)
        {return grid_.isValidCell(row, col);}
    
    bool isLiquidCell(const int& row, const int& col)
        {return getCell(row, col).type == LIQUID;}

    int getCellSize() const 
        {return grid_.getCellSize();}

    
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
