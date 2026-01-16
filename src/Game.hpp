#pragma once 

#include "include/raylib.h"
#include "Menu.hpp"
#include "Material.hpp"
#include "Simulation.hpp"

class Game{
    Simulation sim;

    bool isGameActive = true;
    // int brushSize = 1;
    SimMaterial currentMaterial = getMaterial(SAND);

    void mouseControlls();
    void keyboardControlls();
public:
    Game(const int& rows, const int& cols, const int& cellSize)
        : sim(rows, cols, cellSize) {}   
        
    void simulation(){sim.simulate();}
    void gameControlls();
    void draw(){sim.draw();}
};
