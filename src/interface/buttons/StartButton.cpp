#include "StartButton.hpp"
#include "src/Game.hpp"

void StartButton::onClick(){
    DrawRectangleRoundedLinesEx(outlineRect, 0.5, 1, 3, GREEN);
    game_.isGameActive = true;
}