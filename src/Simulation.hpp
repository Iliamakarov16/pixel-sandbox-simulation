#pragma once

#include "include/raylib.h"
#include "Grid.hpp"
#include "Material.hpp"

class Simulation {
private:
    Grid grid;
    Grid tempGrid;
    void simulatePhysics();
    void simulateCollisions();
public:
    Simulation(const int& rows, const int& columns, const int& cellSize) :
    grid(rows, columns, cellSize), tempGrid(rows, columns, cellSize){};

    void simulate();

};
