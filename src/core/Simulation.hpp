#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "SimMaterial.hpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "Title.hpp"
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
    //Temperature system
    std::vector<std::vector<int>> temperature_;
    std::vector<std::vector<int>> nextTemperature_;
    float diffusion;
    float settle;
    int getMaterialBaseTemperature(const SimMaterial& material) const
        {return material.baseTemp;}
    int getAvarageTemperature(const int& row, const int& col) const;
    void updateTemperature();
    void applyTemperature();
    //Physics by material type
    void simulateGranular(const int& row, const int& col, const SimMaterial& material);    
    void simulateLiquid(const int& row, const int& col, const SimMaterial& material);
    void simulateGas(const int& row, const int& col, const SimMaterial& material);
    void simulateStaticSolid(const int& row, const int& col, const SimMaterial& material);
    void simulateDynamicSolid(const int& row, const int& col, const SimMaterial& material);
    void simulateCustom(const int& row, const int& col, const SimMaterial& material);

    //Custom physics 
    void flamePhysics(const int& row, const int& col);
    //Additional behavior
    void steamBehavior(const int& row, const int& col);
    void smokeBehavior(const int& row, const int& col);
    void cloudBehavior(const int& row, const int& col, const SimMaterial& cloud);
    //Interactions by material
    void sandInteractions(const int& row, const int& col);
    void lavaInteractions(const int& row, const int& col);
    //Interactions by material type (runs all interactions for materials of this type)
    void granularInteractions(const int& row, const int& col, const SimMaterial& material);
    void liquidInteractions(const int& row, const int& col, const SimMaterial& material);  
    /// @brief Helper for physics to displace liquid or gas
    void displacement(const int& row_1, const int& col_1, const int& row_2, const int& col_2);
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
    tempGasVx_(rows / cellSize, std::vector<int>(cols / cellSize, 0)),
    temperature_(rows / cellSize, std::vector<int>(cols / cellSize, 25)),
    nextTemperature_(rows / cellSize, std::vector<int>(cols / cellSize, 25)),
    diffusion(0.1), settle(0.03) {};

    int getCellTemperature(const int& row, const int& col) const
        {return isValidCell(row, col) ? temperature_[row][col] : 25;}
    /// @brief Runs all the physics and interactions logic
    void simulate();    

    void setCell(const int& row, const int& col, const SimMaterial& material);

    void draw() const
        { grid_.draw();}

    SimMaterial getCell(const int& row, const int& col) const
        {return grid_.getCell(row, col);}

    void clear()
        {grid_.clear();}

    bool isEmptyForSim(const int& row, const int& col) const
        {return grid_.isEmptyCell(row, col) && tempGrid_.isEmptyCell(row, col);}

    bool isValidCell(const int& row, const int& col) const
        {return grid_.isValidCell(row, col);}
    
    bool isLiquidCell(const int& row, const int& col) const 
        {return getCell(row, col).type == LIQUID;}

    int getCellSize() const 
        {return grid_.getCellSize();}
        
    void setTitleGrid()
        {grid_.setCells(getTitleGrid());}
        
    SimMaterial getColoredMaterial(MaterialID id)
        {return varyColor(getMaterial(id));}
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
