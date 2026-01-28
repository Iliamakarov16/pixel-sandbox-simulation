#pragma once

#include "Button.hpp"

class Game;

class StartButton : public Button{
public:
    StartButton(const float x, const float y, const std::string& text, const Color& textColor, const Color& buttonColor, Game& game) 
    : Button(x, y, text, textColor, buttonColor, game){};

    void onClick() override;
};
