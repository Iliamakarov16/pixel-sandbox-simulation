#pragma once 

#include "include/raylib.h"
#include "core/SimMaterial.hpp"
#include "core/Simulation.hpp"
#include "interface/Menu.hpp"
#include "interface/buttons/StartButton.hpp"
#include <iostream>

class Game{
    Simulation sim;

    int fps;
    bool drawGameInfo;
    int brushSize;
    bool isCircleBrush;
    bool ignoreMouseUntilRelease;

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
    StartButton startButton;
public:
    bool isGameActive;

    Game(const int& rows, const int& cols, const int& cellSize)
        : sim(rows * 0.75/*75% of window is game field*/, cols, cellSize),
        drawGameInfo(false),
        brushSize(5), 
        isCircleBrush(false), 
        ignoreMouseUntilRelease(false),
        currentMaterial(getMaterial(SAND)),
        menu_(*this, static_cast<int>(rows * 0.75), DARKGRAY),
        startButton(cols/2 - 100, rows/2, "Start", 50, BLACK, WHITE, *this),
        isGameActive(false) {}  

    
    void update();
    
    void gameControls();

    void draw();

    void setCurrentMaterial(MaterialID id)
        { currentMaterial = getMaterial(id); }

    SimMaterial getCurrentMaterial() const
        { return currentMaterial; }

    void setTitleGrid()
        { sim.setTitleGrid(); }

    bool eventTriggered(double interval);
    void clear()
        { sim.clear(); }
};
