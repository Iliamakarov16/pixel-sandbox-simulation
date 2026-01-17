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

    void mouseControls();
    void keyboardControls();
public:
    Game(const int& rows, const int& cols, const int& cellSize)
        : sim(rows, cols, cellSize) {}   
        
    void simulation(){sim.simulate();}
    void gameControls();
    void draw(){sim.draw();}
};
