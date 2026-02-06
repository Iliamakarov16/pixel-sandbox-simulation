#pragma once

#include "Button.hpp"

class Game;

class StartButton : public Button{
public:
    StartButton(const float x, const float y, const std::string& text, const int& textSize, const Color& textColor, const Color& buttonColor, Game& game) 
    : Button(x, y, text, textSize, textColor, buttonColor, game){};

    void onClick() override;
};
