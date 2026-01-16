#pragma once 

#include "include/raylib.h"
#include "Menu.hpp"
#include "Material.hpp"
#include "Simulation.hpp"

class Game{
    Simulation sim;

    bool isGameActive = true;
    int brushSize = 1;
    SimMaterial currentMaterial = MATERIALS[SAND];

    void mouseControlls();
public:
    Game(const int& rows, const int& cols, const int& cellSize)
        : sim(rows, cols, cellSize) {}          
    void physics(){sim.simulate();}
    void gameControlls();
    void draw(){sim.draw();}
};
