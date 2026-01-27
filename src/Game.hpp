#pragma once 

#include "include/raylib.h"
#include "core/SimMaterial.hpp"
#include "core/Simulation.hpp"
#include "interface/Menu.hpp"
#include <iostream>

class Game{
    Simulation sim;

    bool isGameActive;
    double lastUpdateTime;
    int fps;

    int brushSize;
    bool isCircleBrush;

    SimMaterial currentMaterial;
    Menu menu_;
    
    void changeBrushSize();

    void drawSquareBrush();
    void applySquareBrush();

    void drawCircleBrush();
    void applyCircleBrush();

    void applyBrush();
    
    void mouseControls();
    void keyboardControls();

    void drawCellInfo();
public:
    Game(const int& rows, const int& cols, const int& cellSize)
        : sim(rows * 0.75/*75% of window is game field*/, cols, cellSize), 
        isGameActive(true),
        lastUpdateTime(0.0),
        brushSize(5), 
        isCircleBrush(false), 
        currentMaterial(getMaterial(SAND)),
        menu_(*this, static_cast<int>(rows * 0.75), DARKGRAY) {}   
        
    void update();
    void gameControls();
    void draw();
    void setCurrentMaterial(MaterialID id)
        { currentMaterial = getMaterial(id); }
    SimMaterial getCurrentMaterial() const
        {return currentMaterial;}
    void setTitle(){ sim.setGrid();}
};
