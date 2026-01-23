#pragma once 

#include "include/raylib.h"
#include "buttons/Button.hpp"
#include "buttons/MaterialButton.hpp"
#include "src\SimMaterial.hpp"
#include <memory>
#include <vector>

class Game;

class Menu{
private:
    Game& game_;
    std::vector<std::unique_ptr<Button>> buttons_;
    Rectangle bounds_;
    Color color_;
public:
    Menu(Game& game, int menuTopRow, Color color);
    void update();
    void draw() const;

};
