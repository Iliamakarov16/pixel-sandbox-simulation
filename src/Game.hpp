#pragma once 

#include "include/raylib.h"
#include "SimMaterial.hpp"
#include "Simulation.hpp"
#include <iostream>

class Game{
    Simulation sim;

    bool isGameActive;
    int brushSize;
    bool isCircleBrush;
    SimMaterial currentMaterial;
    
    void changeBrushSize();

    void drawSquareBrush();
    void applySquareBrush();

    void drawCircleBrush();
    void applyCircleBrush();

    void applyBrush();
    
    void mouseControls();
    void keyboardControls();
public:
    Game(const int& rows, const int& cols, const int& cellSize)
        : sim(rows, cols, cellSize), isGameActive(true), brushSize(1), isCircleBrush(false), currentMaterial(getMaterial(SAND)) {}   
        
    void simulation(){sim.simulate();}
    void gameControls();
    void draw();
};
