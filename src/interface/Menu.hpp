#pragma once 

#include "include/raylib.h"
#include "buttons/Button.hpp"
#include "buttons/MaterialButton.hpp"
#include "src/core/SimMaterial.hpp"
#include <memory>
#include <vector>

class Game;

class Menu{
private:
    Game& game_;
    std::vector<MaterialButton> materialButtons_;
    Rectangle bounds_;
    Color color_;
public:
    /// @brief Initializes menu and buttons for all materials
    Menu(Game& game, int menuTopRow, Color color);
    
    /// @brief 
    void update();
    void draw() const;

};
